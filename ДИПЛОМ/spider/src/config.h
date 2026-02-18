#pragma once

#include <string>

struct Config {
    // Database
    std::string db_host     = "localhost";
    int         db_port     = 5432;
    std::string db_name;
    std::string db_user;
    std::string db_password;

    // Spider
    std::string start_url;
    int         max_depth   = 1;

    bool load(const std::string& filename);
};