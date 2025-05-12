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

void remove_dynamic_array_head(int*& arr, int& logical_size, int& actual_size) {
    if (logical_size == 0) {
        cout << "Невозможно удалить первый элемент, так как массив пустой. До свидания!" << endl;
        return;
    }

    logical_size--;

    if (logical_size <= actual_size / 3) {
        int new_actual_size = actual_size / 3;
        if (new_actual_size < 1) new_actual_size = 1;

        int* new_arr = new int[new_actual_size];

        for (int i = 0; i < logical_size; i++) {
            new_arr[i] = arr[i + 1];
        }

        actual_size = new_actual_size;
        delete[] arr;
        arr = new_arr;
    }
    else {
        for (int i = 0; i < logical_size; i++) {
            arr[i] = arr[i + 1];
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

    while (true) {
        char answer;
        cout << "\nУдалить первый элемент? (y/n): ";
        cin >> answer;

        if (answer == 'n') {
            print_dynamic_array(arr, logicSize, factSize);
            break;
        }
        else if (answer == 'y') {
            if (logicSize == 0) {
                cout << "\nНевозможно удалить первый элемент, так как массив пустой. До свидания!" << endl;
                break;
            }

            remove_dynamic_array_head(arr, logicSize, factSize);
            print_dynamic_array(arr, logicSize, factSize);
        }
        else {
            cout << "\nПожалуйста, введите 'y' или 'n'." << endl;
        }
    }

    delete[] arr;

    


    return 0;
}

