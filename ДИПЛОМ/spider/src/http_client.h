#pragma once

#include <string>

bool download_page(const std::string& url, std::string& body_out, std::string& error_out);