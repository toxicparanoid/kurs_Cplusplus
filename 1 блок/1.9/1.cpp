#include <iostream>
using namespace std;

void print(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {

    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30};
    int arr3[] = {7, 8, 9, 10};

    cout << "Массив 1: ";
    print(arr1, 5);

    cout << "Массив 2: ";
    print(arr2, 3);

    cout << "Массив 3: ";
    print(arr3, 4);

    return 0;
}