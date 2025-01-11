#include <iostream>
#include <fstream>

int main() {
    int size;

    std::cout << "Введите размер массива: ";
    std::cin >> size;

    if (size <= 0) {
        std::cerr << "Размер массива должен быть положительным числом!" << std::endl;
        return 1;
    }

    int* arr = new int[size];

    std::cout << "Введите элементы массива:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << "-ый элемент: " ;
        std::cin >> arr[i];
    }

    std::ofstream file("3.txt");
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        delete[] arr;
        return 1;
    }

    file << size << std::endl;

    for (int i = size - 1; i >= 0; i--) {
        file << arr[i] << " ";
    }

    file.close();

    delete[] arr;

    std::cout << "Готово, проверьте файл 3.txt!" << std::endl;

    return 0;
}