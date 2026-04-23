#include "config.h"
#include "text_processor.h"
#include "thread_pool.h"
#include "db_manager.h"

#include <unordered_map>

namespace fs = std::filesystem;

std::mutex db_mutex;   // для синхронизации доступа к объекту db_manager, если придётся делить одно соединение
                       // но в нашем случае каждый поток будет открывать своё, поэтому мьютекс пока не нужен.

bool should_skip_directory(const fs::path& path) {
    std::string dir_name = path.filename().string();
    if (dir_name == "build" || dir_name == ".vs" ||
        dir_name == "Debug" || dir_name == "Release" ||
        dir_name == "CMakeFiles" || dir_name == ".git") {
        return true;
    }
    return false;
}

int main() {
    std::cout << "=== Search Engine Indexer ===\n\n";

    Config cfg;
    cfg.load("config.ini");
    cfg.print();

    // Инициализация БД
    DBManager db(cfg.db_host, cfg.db_port, cfg.db_name, cfg.db_user, cfg.db_password);
    if (!db.initialize()) {
        std::cerr << "[ERROR] Database initialization failed. Exiting.\n";
        return 1;
    }

    // Очистка таблиц перед индексацией (для отладки, потом можно убрать или сделать опциональным)
    if (!db.clear_tables()) {
        std::cerr << "[ERROR] Could not clear tables. Exiting.\n";
        return 1;
    }

    std::cout << "Starting indexing from: " << cfg.start_directory << "\n\n";

    if (!fs::exists(cfg.start_directory)) {
        std::cerr << "[ERROR] Directory not found: " << cfg.start_directory << "\n";
        return 1;
    }

    ThreadPool pool(0);
    std::atomic<int> files_processed{0};
    std::atomic<int> total_words{0};

    std::cout << "[INFO] Scanning and processing files...\n";

    for (const auto& entry : fs::recursive_directory_iterator(cfg.start_directory,
                                                             fs::directory_options::skip_permission_denied)) {

        if (entry.is_directory() && should_skip_directory(entry.path())) continue;
        if (!entry.is_regular_file()) continue;

        std::string ext = entry.path().extension().string();
        if (ext.empty()) continue;
        ext = ext.substr(1);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        if (!cfg.extensions_set.count(ext)) continue;

        fs::path file_path = entry.path();
        std::string filename = file_path.filename().string();

        pool.enqueue([file_path, filename, &db, &files_processed, &total_words]() {
            std::ifstream file(file_path);
            if (!file.is_open()) return;

            std::string content((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

            auto words = split_and_clean(content);
            if (words.empty()) return;

            // подсчёт частот в памяти
            std::unordered_map<std::string, int> freq_map;
            for (const auto& w : words) {
                freq_map[w]++;
            }

            // запись в БД: открываем своё соединение
            try {
                // Создаём менеджер с теми же параметрами, но открываем своё соединение
                DBManager local_db(db);   // используем копирование conn_string

                int doc_id = local_db.insert_document(filename);
                if (doc_id < 0) {
                    std::cerr << "[ERROR] Could not insert document: " << filename << std::endl;
                    return;
                }

                for (const auto& [word, freq] : freq_map) {
                    int word_id = local_db.insert_word(word);
                    if (word_id < 0) {
                        std::cerr << "[ERROR] Could not insert word: " << word << std::endl;
                        continue;
                    }
                    local_db.insert_word_frequency(doc_id, word_id, freq);
                }

                files_processed++;
                total_words += static_cast<int>(words.size());
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] In thread: " << e.what() << std::endl;
            }
        });
    }

    pool.wait();

    std::cout << "\n[INFO] Indexing finished.\n";
    std::cout << "Files processed: " << files_processed << std::endl;
    std::cout << "Total words found: " << total_words << std::endl;

    return 0;
}