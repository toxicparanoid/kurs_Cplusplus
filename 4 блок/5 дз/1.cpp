#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    string text;
    getline(cin, text);
    
    map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }
    
    multimap<int, char, greater<int>> sorted_freq;
    for (const auto& pair : freq) {
        sorted_freq.emplace(pair.second, pair.first);
    }
    
    for (const auto& pair : sorted_freq) {
        cout << pair.second << ": " << pair.first << endl;
    }
    
    return 0;
}