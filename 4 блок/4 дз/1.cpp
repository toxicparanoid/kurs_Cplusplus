#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>
using namespace std;

template<typename T>
T quadr(T a) {
    return a * a;
}

template<typename T>
vector<T> quadr(vector<T> a) {
    vector<T> b;
    for (auto i : a) {
        i = i * i;
        b.push_back(i);
    }
    return b;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "[IN]: ";
    int a;
    cin >> a;
    cout << "[OUT]: " << quadr(a) << endl;

    vector<int> b = {-1, 4, 5};

    cout << "[IN]: ";
    for (int i : b) {
        cout << i << " ";
    }
    auto c = quadr(b);
    cout << "\n[OUT]: ";
    for (auto i : c) {
        cout << i << " ";
    }

    return 0;
}