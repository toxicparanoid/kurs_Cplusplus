#include "HTML_parser.h"
#include <gumbo.h>
#include <boost/locale.hpp>
#include <sstream>
#include <regex>
#include <algorithm>

namespace bl = boost::locale;

// Рекурсивный сбор чистого текста (пропускаем <script>, <style>, <head>)
void extract_text_recursive(GumboNode* node, std::string& out_text) {
    if (node->type == GUMBO_NODE_TEXT) {
        out_text += std::string(node->v.text.text) + " ";
    } else if (node->type == GUMBO_NODE_ELEMENT) {
        GumboTag tag = node->v.element.tag;
        // Пропускаем ненужные теги
        if (tag == GUMBO_TAG_SCRIPT || tag == GUMBO_TAG_STYLE || tag == GUMBO_TAG_HEAD ||
            tag == GUMBO_TAG_NOFRAMES || tag == GUMBO_TAG_NOSCRIPT) {
            return;
        }

        // Рекурсия по детям
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            extract_text_recursive(static_cast<GumboNode*>(children->data[i]), out_text);
        }
    }
    // Игнорируем комментарии, CDATA и т.д.
}

// Рекурсивный сбор ссылок <a href="...">
void extract_links_recursive(GumboNode* node, std::vector<std::string>& out_links, const std::string& base_url) {
    if (node->type == GUMBO_NODE_ELEMENT && node->v.element.tag == GUMBO_TAG_A) {
        GumboAttribute* href_attr = gumbo_get_attribute(&node->v.element.attributes, "href");
        if (href_attr && href_attr->value) {
            std::string href = href_attr->value;

            // Фильтруем ненужные ссылки
            if (href.empty() || href[0] == '#' || 
                href.find("mailto:") == 0 || href.find("javascript:") == 0 ||
                href.find("tel:") == 0) {
                return;
            }

            // Преобразуем относительные ссылки в абсолютные (простой вариант)
            if (href.find("http://") != 0 && href.find("https://") != 0) {
                // Если начинается с / — добавляем хост
                if (href[0] == '/') {
                    size_t slash_pos = base_url.find('/', 8); // после http://
                    if (slash_pos != std::string::npos) {
                        href = base_url.substr(0, slash_pos) + href;
                    } else {
                        href = base_url + href;
                    }
                } else {
                    // Если без / — добавляем слеш
                    href = base_url + "/" + href;
                }
            }

            out_links.push_back(href);
        }
    }

    // Рекурсия по детям
    if (node->type == GUMBO_NODE_ELEMENT) {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            extract_links_recursive(static_cast<GumboNode*>(children->data[i]), out_links, base_url);
        }
    }
}

ParsedPage parse_html(const std::string& html, const std::string& base_url)
{
    ParsedPage result;

    GumboOutput* output = gumbo_parse_with_options(&kGumboDefaultOptions, html.c_str(), html.size());
    if (!output) {
        std::cerr << "[Gumbo] Failed to parse HTML\n";
        return result;
    }

    // 1. Title
    GumboNode* head = nullptr;
    GumboVector* root_children = &output->root->v.element.children;
    for (unsigned int i = 0; i < root_children->length; ++i) {
        GumboNode* child = static_cast<GumboNode*>(root_children->data[i]);
        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD) {
            head = child;
            break;
        }
    }

    if (head) {
        GumboVector* head_children = &head->v.element.children;
        for (unsigned int i = 0; i < head_children->length; ++i) {
            GumboNode* child = static_cast<GumboNode*>(head_children->data[i]);
            if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE) {
                GumboVector* title_children = &child->v.element.children;
                if (title_children->length > 0) {
                    GumboNode* text_node = static_cast<GumboNode*>(title_children->data[0]);
                    if (text_node->type == GUMBO_NODE_TEXT) {
                        result.title = text_node->v.text.text;
                    }
                }
                break;
            }
        }
    }

    // 2. Чистый текст
    std::string raw_text;
    extract_text_recursive(output->root, raw_text);

    // Очистка текста
    raw_text = bl::to_lower(raw_text, bl::generator().generate("en_US.UTF-8")); // или ru_RU.UTF-8 для русского

    std::regex punct_re(R"([^\w\s])");
    raw_text = std::regex_replace(raw_text, punct_re, " ");

    std::regex spaces_re(R"(\s+)");
    raw_text = std::regex_replace(raw_text, spaces_re, " ");

    result.clean_text = raw_text;

    // 3. Частота слов
    std::istringstream iss(raw_text);
    std::string word;
    while (iss >> word) {
        if (word.length() >= 3 && word.length() <= 32) {
            result.word_freq[word]++;
        }
    }

    // 4. Ссылки
    extract_links_recursive(output->root, result.links, base_url);

    gumbo_destroy_output(&kGumboDefaultOptions, output);

    // Отладочный вывод
    std::cout << "[Gumbo] Parsed title: " << result.title << "\n";
    std::cout << "[Gumbo] Clean text length: " << result.clean_text.size() << " chars\n";
    std::cout << "[Gumbo] Found " << result.links.size() << " links\n";
    std::cout << "[Gumbo] Unique words: " << result.word_freq.size() << "\n";

    if (!result.word_freq.empty()) {
        std::vector<std::pair<std::string, int>> sorted(result.word_freq.begin(), result.word_freq.end());
        std::sort(sorted.rbegin(), sorted.rend(), [](const auto& a, const auto& b){ return a.second > b.second; });
        std::cout << "Top 5 words:\n";
        for (size_t i = 0; i < std::min<size_t>(5, sorted.size()); ++i) {
            std::cout << "  " << sorted[i].first << ": " << sorted[i].second << "\n";
        }
    }

    if (!result.links.empty()) {
        std::cout << "First few links:\n";
        for (size_t i = 0; i < std::min<size_t>(5, result.links.size()); ++i) {
            std::cout << "  " << result.links[i] << "\n";
        }
    }

    return result;
}