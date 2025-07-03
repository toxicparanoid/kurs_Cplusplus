#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <ctime>
#include <algorithm>
#include <stdexcept>
using namespace std;

void colaps(vector<int>& a) {
    sort(a.begin(), a.end());
    auto it = unique(a.begin(), a.end());
    a.erase(it, a.end());
}

void get_VECTOR(vector<int> a) {
    for (int i : a) {
        cout << i << " ";
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    
    vector<int> vec = {1, 1, 2, 5, 6, 1, 2, 4};

    cout << "[IN]: ";
    get_VECTOR(vec);

    colaps(vec);

    cout << "\n[OUT]: ";
    get_VECTOR(vec);

    return 0;
}