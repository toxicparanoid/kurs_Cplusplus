#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string filename = "1.txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Файл не найден. Создаем новый файл." << std::endl;

        std::ofstream newFile(filename);
        if (newFile.is_open()) {
            std::cout << "Файл успешно создан." << std::endl;
            newFile.close();
        } else {
            std::cerr << "Не удалось создать файл!" << std::endl;
            return 1;
        }
    } else {
        file.close(); 
    }

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл для чтения!" << std::endl;
        return 1;
    }

    std::string word;
    while (inputFile >> word) {
        std::cout << word << std::endl;
    }

    inputFile.close();

    return 0;
}