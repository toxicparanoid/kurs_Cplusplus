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

void append_to_dynamic_array(int*& arr, int& logical_size, int& actual_size, int new_element) {
    if (logical_size < actual_size) {
        arr[logical_size] = new_element;
        logical_size++;
    }
    else {
        int new_actual_size = actual_size * 2;
        if (actual_size == 0) new_actual_size = 1;

        int* new_arr = new int[new_actual_size];

        for (int i = 0; i < actual_size; i++) {
            new_arr[i] = arr[i];
        }

        new_arr[logical_size] = new_element;
        logical_size++;
        actual_size = new_actual_size;

        delete[] arr;
        arr = new_arr;
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

    while (true) {
        int new_element;
        cout << "\nВведите элемент для добавления (0 для выхода): ";
        cin >> new_element;

        if (new_element == 0) {
            break;
        }

        append_to_dynamic_array(arr, logicSize, factSize, new_element);
        print_dynamic_array(arr, logicSize, factSize);
    }

    cout << "\nСпасибо! Ваш массив: ";
    print_dynamic_array(arr, logicSize, factSize);

    delete[] arr;

    


    return 0;
}

