#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>
using namespace std;

template <typename T>
class Table {
private:
    int rows_;
    int cols_;
    vector<vector<T>> data_;
public:
    Table(int rows, int cols) : rows_(rows), cols_(cols) {
        data_ = vector<vector<T>>(rows, vector<T>(cols));
    }
    
    vector<T>& operator[](int row) {
        return data_[row];
    }
    
    const vector<T>& operator[](int row) const {
        return data_[row];
    }
    
    pair<int, int> Size() const {
        return {rows_, cols_};
    }
};

int main() {
    Table<int> test(2, 3);
    test[0][0] = 4;
    cout << test[0][0] << endl;
    
    auto size = test.Size();
    cout << "rows: " << size.first << ", cols: " << size.second << endl;
    
    return 0;
}