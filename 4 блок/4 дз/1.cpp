#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>
using namespace std;

template<typename T>
T quadr(T num) {
    return num * num;
}

template<typename T>
vector<T> quadr(vector<T> vec) {
    vector<T> vecNew;
    for (auto step : vec) {
        step = step * step;
        vecNew.push_back(step);
    }
    return vecNew;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "[IN]: ";
    int a;
    cin >> a;
    cout << "[OUT]: " << quadr(a) << endl;

    vector<int> vec = {-1, 4, 5};

    cout << "[IN]: ";
    for (int step : vec) {
        cout << step << " ";
    }
    auto vecQuadr = quadr(vec);
    cout << "\n[OUT]: ";
    for (auto step : vecQuadr) {
        cout << step << " ";
    }

    return 0;
}