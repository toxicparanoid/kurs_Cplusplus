#include "config.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>

bool Config::load(const std::string& filename)
{
    namespace pt = boost::property_tree;
    pt::ptree tree;

    try {
        pt::read_ini(filename, tree);

        db_host     = tree.get<std::string>("database.host", db_host);
        db_port     = tree.get<int>("database.port", db_port);
        db_name     = tree.get<std::string>("database.dbname");
        db_user     = tree.get<std::string>("database.user");
        db_password = tree.get<std::string>("database.password");

        start_url   = tree.get<std::string>("spider.start_url");
        max_depth   = tree.get<int>("spider.max_depth", max_depth);

        if (db_name.empty() || start_url.empty()) {
            std::cerr << "Error: missing required parameters (dbname or start_url)\n";
            return false;
        }

        std::cout << "Loaded configuration:\n";
        std::cout << "  Database: " << db_host << ":" << db_port << "/" << db_name << "\n";
        std::cout << "  Username: " << db_user << "\n";
        std::cout << "  Start URL: " << start_url << "\n";
        std::cout << "  Max depth: " << max_depth << "\n";

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Config loading error: " << e.what() << "\n";
        return false;
    }
}