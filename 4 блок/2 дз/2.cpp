#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>
using namespace std;

class smart_array {
private:
    int* data;
    size_t capacity;
    size_t size;

public:
    smart_array(size_t cap) : capacity(cap), size(0) {
        if (cap == 0) {
            throw std::invalid_argument("Емкость массива должна быть < 0");
        }
        data = new int[cap];
    }

    smart_array(const smart_array& other) : capacity(other.capacity), size(other.size) {
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    smart_array& operator=(const smart_array& other) {
        if (this != &other) {
            delete[] data;
            
            capacity = other.capacity;
            size = other.size;
            data = new int[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~smart_array() {
        delete[] data;
    }

    void add_element(int element) {
        if (size >= capacity) {
            size_t new_capacity = capacity * 2;
            int* new_data = new int[new_capacity];
            
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        
        data[size] = element;
        size++;
    }

    int get_element(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс за пределами допустимого");
        }
        return data[index];
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44); 
        new_array.add_element(34);

        arr = new_array;

        cout << arr.get_element(0) << endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}