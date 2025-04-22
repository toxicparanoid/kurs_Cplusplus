#include <iostream>
#include <vector>
using namespace std;

void merge_sort(int* arr, int size) {
    if (size <= 1) return;

    int pivot = arr[size / 2];
    int i = 0, j = size - 1;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) swap(arr[i++], arr[j--]);
    }

    merge_sort(arr, j + 1);
    merge_sort(arr + i, size - i);
}

int main() {
    setlocale(LC_ALL, "rus");

    
    int arr[] = { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62, 62, 62 };

    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    for (int i : arr) {
        cout << i << " ";
    }

    cout << endl;

    merge_sort(arr, size);
    cout << "Отсортированный массив: ";
    for (int i : arr) {
        cout << i << " ";
    }

    return 0;
}