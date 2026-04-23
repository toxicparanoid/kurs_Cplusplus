#pragma once
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <mutex>
#include <sstream>

struct Config {
    // Database
    std::string db_host = "localhost";
    std::string db_port = "5432";
    std::string db_name = "search_engine";
    std::string db_user = "postgres";
    std::string db_password = "put_here_your_own_password";

    // Indexer
    std::string start_directory = ".";
    std::string file_extensions = "txt,md,log,cpp,h,hpp";

    std::set<std::string> extensions_set;

    bool load(const std::string& filename);
    void print() const;
    void parse_extensions();
};