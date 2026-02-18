#include "config.h"
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

    std::cout << "Config loaded successfully!\n";
    return 0;
}