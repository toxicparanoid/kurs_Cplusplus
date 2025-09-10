#include <iostream>
#include <vector>
#include <future>
#include <iterator>
#include <algorithm>
using namespace std;

constexpr size_t MIN_BLOCK_SIZE = 1000;

template <typename Iterator, typename Func>
void parallel_for_each_impl(Iterator begin, Iterator end, Func& func, size_t threshold) {
    auto distance = std::distance(begin, end);
    
    if (distance <= static_cast<typename iterator_traits<Iterator>::difference_type>(threshold)) {
        for_each(begin, end, func);
        return;
    }
    
    Iterator mid = begin;
    advance(mid, distance / 2);
    
    auto future = async(launch::async, 
                            parallel_for_each_impl<Iterator, Func>,
                            begin, mid, ref(func), threshold);
    
    parallel_for_each_impl(mid, end, func, threshold);
    
    future.get();
}

template <typename Iterator, typename Func>
void parallel_for_each(Iterator begin, Iterator end, Func func) {
    parallel_for_each_impl(begin, end, func, MIN_BLOCK_SIZE);
}

int main() {
    vector<int> vec(10000);
    
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = static_cast<int>(i + 1);
    }
    
    auto multiply_by_two = [](int& x) { x *= 2; };
    
    cout << "BEFORE OBRABOTKA: ";
    for (size_t i = 0; i < 10; ++i) {
        cout << vec[i] << " ";
    }
    cout << "..." << endl;
    
    parallel_for_each(vec.begin(), vec.end(), multiply_by_two);
    
    cout << "AFTER OBRABOTKA: ";
    for (size_t i = 0; i < 10; ++i) {
        cout << vec[i] << " ";
    }
    cout << "..." << endl;
    
    return 0;
}