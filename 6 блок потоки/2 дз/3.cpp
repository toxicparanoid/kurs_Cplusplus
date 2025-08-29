#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

using namespace std;

class Data {
private:
    int value;
    mutable mutex mtx;

public:
    Data(int val = 0) : value(val) {}
    
    Data(const Data& other) {
        lock_guard<mutex> lock(other.mtx);
        value = other.value;
    }
    
    Data& operator=(const Data& other) {
        if (this != &other) {
            lock(mtx, other.mtx);
            lock_guard<mutex> lock1(mtx, adopt_lock);
            lock_guard<mutex> lock2(other.mtx, adopt_lock);
            value = other.value;
        }
        return *this;
    }
    
    int getValue() const {
        lock_guard<mutex> lock(mtx);
        return value;
    }
    
    void setValue(int val) {
        lock_guard<mutex> lock(mtx);
        value = val;
    }
    
    void print(const string& name) const {
        lock_guard<mutex> lock(mtx);
        cout << name << ": value = " << value << endl;
    }
    
    friend void swap_with_lock(Data& a, Data& b);
    friend void swap_with_scoped_lock(Data& a, Data& b);
    friend void swap_with_unique_lock(Data& a, Data& b);
};

void swap_with_lock(Data& a, Data& b) {
    lock(a.mtx, b.mtx);
    
    lock_guard<mutex> lock_a(a.mtx, adopt_lock);
    lock_guard<mutex> lock_b(b.mtx, adopt_lock);
    
    swap(a.value, b.value);
    
    cout << "Swap completed using lock() + lock_guard" << endl;
}

void swap_with_scoped_lock(Data& a, Data& b) {
    scoped_lock lock(a.mtx, b.mtx);
    
    swap(a.value, b.value);
    
    cout << "Swap completed using scoped_lock" << endl;
}

void swap_with_unique_lock(Data& a, Data& b) {
    unique_lock<mutex> lock_a(a.mtx, defer_lock);
    unique_lock<mutex> lock_b(b.mtx, defer_lock);
    
    lock(lock_a, lock_b);
    
    swap(a.value, b.value);
    
    cout << "Swap completed using unique_lock + lock()" << endl;
}

void demonstrate_swap() {
    Data data1(10);
    Data data2(20);
    
    cout << "Before swap:" << endl;
    data1.print("data1");
    data2.print("data2");
    cout << endl;
    
    swap_with_lock(data1, data2);
    cout << "After swap_with_lock:" << endl;
    data1.print("data1");
    data2.print("data2");
    cout << endl;
    
    data1.setValue(10);
    data2.setValue(20);
    
    swap_with_scoped_lock(data1, data2);
    cout << "After swap_with_scoped_lock:" << endl;
    data1.print("data1");
    data2.print("data2");
    cout << endl;
    
    data1.setValue(10);
    data2.setValue(20);
    
    swap_with_unique_lock(data1, data2);
    cout << "After swap_with_unique_lock:" << endl;
    data1.print("data1");
    data2.print("data2");
}

void thread_test(Data& a, Data& b, int thread_id) {
    for (int i = 0; i < 3; ++i) {
        cout << "Thread " << thread_id << " attempt " << i + 1 << ":" << endl;
        
        if (thread_id % 3 == 0) {
            swap_with_lock(a, b);
        } else if (thread_id % 3 == 1) {
            swap_with_scoped_lock(a, b);
        } else {
            swap_with_unique_lock(a, b);
        }
        
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    
    cout << "=== Демонстрация работы функций swap ===" << endl;
    demonstrate_swap();
    
    cout << "\n=== Многопоточное тестирование ===" << endl;
    Data data3(100);
    Data data4(200);
    
    thread t1(thread_test, ref(data3), ref(data4), 1);
    thread t2(thread_test, ref(data3), ref(data4), 2);
    thread t3(thread_test, ref(data3), ref(data4), 3);
    
    t1.join();
    t2.join();
    t3.join();
    
    cout << "\nFinal values:" << endl;
    data3.print("data3");
    data4.print("data4");
    
    return 0;
}