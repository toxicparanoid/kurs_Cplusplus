#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <pugixml.hpp>

struct ParsedPage {
    std::string title;                       // <title> если есть
    std::string clean_text;                  // весь текст без тегов
    std::vector<std::string> links;          // все найденные абсолютные/относительные href
    std::map<std::string, int> word_freq;    // слово → частота (после очистки)
};

ParsedPage parse_html(const std::string& html, const std::string& base_url);