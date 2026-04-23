#include "config.h"
#include "text_processor.h"
#include "thread_pool.h"

namespace fs = std::filesystem;

struct FileResult {
    std::string filename;
    int word_count;
};

std::mutex results_mutex;

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

    std::cout << "Starting indexing from: " << cfg.start_directory << "\n\n";

    if (!fs::exists(cfg.start_directory)) {
        std::cerr << "[ERROR] Directory not found: " << cfg.start_directory << "\n";
        return 1;
    }

    ThreadPool pool(0);

    std::vector<FileResult> results;
    int total_words = 0;
    int files_queued = 0;

    std::cout << "[INFO] Scanning files and queuing tasks...\n";

    //сканируем и ставим все файлы в очередь
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
        files_queued++;

        pool.enqueue([file_path, &results, &total_words]() {
            std::ifstream file(file_path);
            if (!file.is_open()) return;

            std::string content((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

            auto words = split_and_clean(content);
            int wcount = static_cast<int>(words.size());

            if (wcount > 0) {
                std::lock_guard<std::mutex> lock(results_mutex);
                results.push_back({file_path.filename().string(), wcount});
                total_words += wcount;
            }
        });
    }

    std::cout << "[INFO] Total files queued: " << files_queued << "\n";
    std::cout << "Waiting for all threads to complete...\n\n";

    //ждём когда все потоки полностью закончат работу
    pool.wait();

    //вывод рещультатов
    std::cout << "=== Indexing finished ===\n\n";

    std::sort(results.begin(), results.end(), 
              [](const FileResult& a, const FileResult& b) {
                  return a.filename < b.filename;
              });

    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " 
                  << results[i].filename 
                  << "  (" << results[i].word_count << " words)\n";
    }

    std::cout << "\nProcessed " << results.size() << " files\n";
    std::cout << "Total words found: " << total_words << "\n\n";

    return 0;
}