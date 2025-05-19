#include <iostream>
#include <string>
using namespace std;


void print_pyramid(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (i == 0){
            cout << i << " root " << arr[i] << endl;
        }
        else {
            int level = 0;
            int temp = i + 1;
            while (temp > 1) {
                temp /= 2;
                level++;
            }

            int parent_index = (i - 1) / 2;

            string type = (i % 2 == 1) ? " left  " : " right ";

            cout << level << type << "(" << arr[parent_index] << ") " << arr[i] << endl;
        }
    }
}

string get_position_info(int index, int* arr, int size) {
    if (index >= size) return "Invalid index";
    
    if (index == 0) {
        return "0 root " + to_string(arr[index]);
    } else {
        int level = 0;
        int temp = index + 1;
        while (temp > 1) {
            temp /= 2;
            level++;
        }
        int parent_index = (index - 1) / 2;
        string child_type = (index % 2 == 1) ? "left" : "right";
        return to_string(level) + " " + child_type + "(" + to_string(arr[parent_index]) + ") " + to_string(arr[index]);
    }
}

void pyramid_navigation(int* arr, int size) {
    int current_index = 0;
    string command;

    while (true) {
        cout << "Вы находитесь здесь: " << get_position_info(current_index, arr, size) << endl;
        cout << "Введите команду: ";
        cin >> command;

        if (command == "exit") {
            break;
        } else if (command == "up") {
            if (current_index == 0) {
                cout << "Ошибка! Отсутствует родитель" << endl;
            } else {
                current_index = (current_index - 1) / 2;
                cout << "Ок" << endl;
            }
        } else if (command == "left") {
            int left_child = 2 * current_index + 1;
            if (left_child >= size) {
                cout << "Ошибка! Отсутствует левый потомок" << endl;
            } else {
                current_index = left_child;
                cout << "Ок" << endl;
            }
        } else if (command == "right") {
            int right_child = 2 * current_index + 2;
            if (right_child >= size) {
                cout << "Ошибка! Отсутствует правый потомок" << endl;
            } else {
                current_index = right_child;
                cout << "Ок" << endl;
            }
        } else {
            cout << "Неизвестная команда. Используйте up, left, right или exit" << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int arr[] = { 1, 3, 6, 5, 9, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
    cout << "Пирамида: " << endl;
    print_pyramid(arr, size);
    pyramid_navigation(arr, size);

    return 0;
}

