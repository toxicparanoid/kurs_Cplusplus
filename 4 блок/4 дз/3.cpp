#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>
using namespace std;

class functor {
private:
    int cnt;
    int sum;
public:
    functor() : cnt{0}, sum{0} {};
    void operator()(vector<int> a) {
        for (int i : a) {
            if (i % 3 == 0) {
                cnt++;
                sum += i;
            }
        }
    }

    void get_vec(vector<int> a) {
        cout << "[IN]: ";
        for (int i : a) {
            cout << i << " ";
        }
        cout << endl;
    }

    void get_sum() {
        cout << "[OUT]: get_sum() = " << sum << endl;
    }

    void get_count() {
        cout << "[OUT]: get_count() = " << cnt << endl;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    vector<int> vec = {4, 1, 3, 6, 25, 54};
    
    functor fun;
    fun.get_vec(vec);
    fun(vec);
    fun.get_sum();
    fun.get_count();

    return 0;
}