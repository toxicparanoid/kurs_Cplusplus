#include <iostream>
#include <fstream>

int main() {
    std::string filename = "2.txt";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }

    int n;
    file >> n;

    int array[n];

    for (int i = 0; i < n; ++i) {
        file >> array[i];
    }

    file.close();

    // //решил поприкалываться, написал алогоритм сортировки пузырьком :)
    // for (int i = 1; i < n; i++) {
    //     for (int j = 0; j < n-i; j++) {
    //         if (array[j] > array[j+1]) {
    //             int temp = array[j];
	// 			array[j] = array[j+1];
	// 			array[j+1] = temp;
    //         }
    //     }
    // }

    // for (int i = 0; i < n; i++) {
    //     std::cout << array[i] << " ";
    // }
    // std::cout << std::endl;

    for (int i = n-1; i >= 0; i--) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}