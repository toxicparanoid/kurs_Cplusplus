#include "config.h"
#include "text_processor.h"
#include "db_manager.h"
#include "config.h"

int main() {
    std::cout << "=== Search Engine Searcher ===\n\n";

    Config cfg;
    if (!cfg.load("config.ini")) {
        std::cerr << "[ERROR] Could not load config.ini\n";
        return 1;
    }
    cfg.print();

    DBManager db(cfg.db_host, cfg.db_port, cfg.db_name, cfg.db_user, cfg.db_password);
    if (!db.initialize()) {
        std::cerr << "[ERROR] Database initialization failed. Exiting.\n";
        return 1;
    }

    std::cout << "\nEnter search queries (words separated by spaces, max 4 words).\n";
    std::cout << "Type '/exit' to quit.\n\n";

    while (true) {
        std::cout << "Query> ";
        std::string input;
        if (!std::getline(std::cin, input)) {
            // EOF или Ctrl+Z
            break;
        }

        input.erase(0, input.find_first_not_of(" \t\r\n"));
        input.erase(input.find_last_not_of(" \t\r\n") + 1);

        if (input == "/exit") {
            std::cout << "Exiting...\n";
            break;
        }

        auto words = split_and_clean(input);
        if (words.empty()) {
            std::cout << "No valid words in query.\n\n";
            continue;
        }

        if (words.size() > 4) {
            std::cout << "Maximum 4 words allowed per query.\n\n";
            continue;
        }

        std::unordered_set<std::string> unique(words.begin(), words.end());
        std::vector<std::string> query(unique.begin(), unique.end());

        try {
            auto results = db.search(query);

            if (results.empty()) {
                std::cout << "No results found.\n\n";
            } else {
                std::cout << "Results (total_freq):\n";
                for (size_t i = 0; i < results.size(); ++i) {
                    std::cout << "[" << i+1 << "] " << results[i].first
                              << " (freq: " << results[i].second << ")\n";
                }
                std::cout << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Internal error during search: " << e.what() << "\n\n";
        }
    }

    return 0;
}