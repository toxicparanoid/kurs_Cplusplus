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
            throw std::out_of_range("Емкость массива должна быть < 0");
        }
        data = new int[cap];
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
        arr.add_element(14);
        arr.add_element(15);

        arr.add_element(42);
        arr.add_element(99);

        std::cout << arr.get_element(5) << std::endl;
        std::cout << arr.get_element(6) << std::endl;

        std::cout << arr.get_element(10) << std::endl;  // исключение
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}