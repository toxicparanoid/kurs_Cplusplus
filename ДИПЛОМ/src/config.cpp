#include "config.h"

bool Config::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[WARNING] Config file not found: " << filename << "\n";
        std::cerr << "Using default values.\n";
        parse_extensions();
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t comment = line.find('#');
        if (comment != std::string::npos)
            line = line.substr(0, comment);

        if (line.empty()) continue;

        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        if (key == "db_host") db_host = value;
        else if (key == "db_port") db_port = value;
        else if (key == "db_name") db_name = value;
        else if (key == "db_user") db_user = value;
        else if (key == "db_password") db_password = value;
        else if (key == "start_directory") start_directory = value;
        else if (key == "file_extensions") file_extensions = value;
    }

    parse_extensions();
    return true;
}

void Config::parse_extensions() {
    extensions_set.clear();
    std::stringstream ss(file_extensions);
    std::string ext;

    while (std::getline(ss, ext, ',')) {
        //убираем пробелы и переводим в нижний регистр
        ext.erase(0, ext.find_first_not_of(" \t"));
        ext.erase(ext.find_last_not_of(" \t") + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        if (!ext.empty()) {
            extensions_set.insert(ext);
        }
    }
}

void Config::print() const {
    std::cout << "=== Configuration Loaded ===\n";
    std::cout << "DB Host        : " << db_host << "\n";
    std::cout << "DB Name        : " << db_name << "\n";
    std::cout << "Start Directory: " << start_directory << "\n";
    std::cout << "Extensions     : " << file_extensions << "\n";
    std::cout << "===========================\n\n";
}