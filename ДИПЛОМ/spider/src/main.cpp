#include "config.h"
#include "http_client.h"
#include "html_parser.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: spider.exe <path_to_config.ini>\n";
        return 1;
    }

    Config cfg;
    if (!cfg.load(argv[1])) {
        std::cerr << "Failed to load config file\n";
        return 1;
    }

    std::cout << "Starting crawler from: " << cfg.start_url << "\n";

    std::string html_content;
    std::string download_error;

    if (download_page(cfg.start_url, html_content, download_error)) {
        std::cout << "Download OK! Content length: " << html_content.size() << " bytes\n";
        std::cout << "First 1500 characters of HTML:\n";
        std::cout << html_content.substr(0, 1500) << "...\n";
    } else {
        std::cerr << "Download failed: " << download_error << "\n";
        return 1;
    }

    ParsedPage parsed = parse_html(html_content, cfg.start_url);

    std::cout << "Parsed " << parsed.links.size() << " links and " << parsed.word_freq.size() << " unique words.\n";

    return 0;
}