#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <algorithm>

std::string to_lower_ascii(const std::string& str);
std::vector<std::string> split_and_clean(const std::string& text);