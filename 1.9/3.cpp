#include <iostream>
using namespace std;

void reverse(int arr[], int size) {
    int left = 0;
    int right = size - 1;
    while (left < right) {
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {5, 10, 15, 20, 25, 30, 35};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "До функции reverse: ";
    printArray(arr, size);

    reverse(arr, size);

    cout << "После функции reverse: ";
    printArray(arr, size);

    return 0;
}