#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
using namespace std;

future<size_t> find_min_index_async(const vector<int>& arr, size_t start, size_t end) {
    promise<size_t> promise;
    auto future = promise.get_future();
    
    async(launch::async, [arr, start, end, promise = std::move(promise)]() mutable {
        size_t min_index = start;
        for (size_t i = start + 1; i < end; ++i) {
            if (arr[i] < arr[min_index]) {
                min_index = i;
            }
        }
        promise.set_value(min_index);
    });
    
    return future;
}

void selection_sort(vector<int>& arr) {
    size_t n = arr.size();
    
    for (size_t i = 0; i < n - 1; ++i) {
        auto future = find_min_index_async(arr, i, n);
        
        size_t min_index = future.get();
        
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Start massive: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    
    selection_sort(arr);
    
    cout << "Sorted massive: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}