#include <iostream>
#include <fstream>

int main() {

    std::ifstream inFile("4.txt");
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл 4.txt!" << std::endl;
        return 1;
    }

    int rows, cols;

    inFile >> rows >> cols;

    if (rows <= 0 || cols <= 0) {
        std::cerr << "Некорректные размеры массива!" << std::endl;
        inFile.close();
        return 1;
    }

    int** array = new int*[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inFile >> array[i][j];
        }
    }

    inFile.close();

    for (int i = 0; i < rows; i++) {
        for (int j = cols - 1; j >= 0; j--) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}