#include <iostream>
using namespace std;

void print_dynamic_array(int* arr, int logical_size, int actual_size) {
    cout << "Ваш динамический массив: ";
    for (int i = 0; i < actual_size; i++) {
        if (i < logical_size) {
            cout << arr[i] << " ";
        }
        else {
            cout << "_ ";
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int factSize, logicSize;

    while (true) {

        cout << "Введите фактический размер массива: ";
        cin >> factSize;

        cout << "Введите логический размер массива: ";
        cin >> logicSize;

        if (logicSize > factSize) {
            cout << "Логический размер не может превышать фактический! Попробуйте снова!\n";
        }
        else break;
    }

    int* arr = new int[factSize];

    for (int i = 0; i < logicSize; i++) {
        cout << "Введите arr[" << i << "]: ";
        cin >> arr[i];
    }

    print_dynamic_array(arr, logicSize, factSize);

    delete[] arr;

    return 0;
}

