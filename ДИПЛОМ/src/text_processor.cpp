#include "text_processor.h"

std::string to_lower_ascii(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>(c + 32);
        }
    }
    return result;
}

std::vector<std::string> split_and_clean(const std::string& text) {
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string token;

    while (ss >> token) {
        token.erase(std::remove_if(token.begin(), token.end(),
            [](unsigned char c) { 
                return !std::isalnum(c); 
            }), token.end());

        if (token.length() >= 2 && token.length() <= 32) {
            words.push_back(to_lower_ascii(token));
        }
    }
    return words;
}