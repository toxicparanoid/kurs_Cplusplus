#include<iostream>

int main(){
    setlocale(LC_ALL, "rus");
//-------------------------------------------------
    std::cout << "1 Задание: " << std::endl;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++){
        if (i == 9){
            std::cout << arr[i];
            break;
        }
        std::cout << arr[i] << ", ";
    }

    std::cout << std::endl << std::endl;;

//-------------------------------------------------
    std::cout << "2 Задание: " << std::endl;

    int ar[5] = {3, 8, 2, 15, 6};
    int min = 10000, max = 0;

    std::cout << "Массив: ";

    for (int i = 0; i < 5; i++) {
        std::cout << ar[i] << " ";
        if (ar[i] < min) {
            min = ar[i];
        }
        if (ar[i] > max) {
            max = ar[i];
        }

    }

    std::cout << std::endl << "Минимальный элемент: " << min << std::endl;
    std::cout << "Максимальный элемент: " << max << std::endl << std::endl;

//-------------------------------------------------
    std::cout << "3 Задание: " << std::endl;

    int rows = 3;
    int cols = 6;
    int array[rows][cols] = {
        {5, 12, 7, 3, 9, 15},
        {8, 2, 14, 6, 11, 4},
        {10, 1, 13, 0, 18, 17}
    };

    std::cout << "Массив:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << array[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    int minIndex[2] = {0, 0};
    int maxIndex[2] = {0, 0};
    int minValue = array[0][0];
    int maxValue = array[0][0];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (array[i][j] < minValue) {
                minValue = array[i][j];
                minIndex[0] = i;
                minIndex[1] = j;
            }
            if (array[i][j] > maxValue) {
                maxValue = array[i][j];
                maxIndex[0] = i;
                maxIndex[1] = j;
            }
        }
    }

    std::cout << "Индекс минимального элемента: " << minIndex[0] << " " << minIndex[1] << "\n";
    std::cout << "Индекс максимального элемента: " << maxIndex[0] << " " << maxIndex[1] << "\n";
    std::cout << std::endl;

//-------------------------------------------------
    std::cout << "4 Задание: " << std::endl;

    int array2[10] = {10, 3, 4, 1, 8, 9, 7, 2, 6, 5};

    std::cout << "Массив до сортировки: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << array2[i] << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 10 - 1; ++i) {
        for (int j = 0; j < 10 - 1 - i; ++j) {
            if (array2[j] > array2[j + 1]) {
                int temp = array2[j];
                array2[j] = array2[j + 1];
                array2[j + 1] = temp;
            }
        }
    }

    std::cout << "Массив после сортировки: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << array2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
