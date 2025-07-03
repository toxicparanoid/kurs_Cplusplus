#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
using namespace std;

template<typename T>
void print_container(T a) {
    for (auto i = a.begin(); i != a.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    vector<string> vec_VECTOR = { "one", "two", "three", "four" };
    list<string> vec_LIST = { "one", "two", "three", "four" };
    set<string> vec_SET = { "one", "two", "three", "four" };

    print_container(vec_SET);
    print_container(vec_LIST);
    print_container(vec_VECTOR);

    return 0;
}