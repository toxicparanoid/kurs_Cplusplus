#include <iostream>
#include <vector>
using namespace std;

void merge_sort(int* arr, int size) {
    if (size <= 1) return;

    int mid = size / 2;
    int* left = arr;
    int* right = arr + mid;

    merge_sort(left, mid);
    merge_sort(right, size - mid);

    vector<int> temp(size);
    int i = 0, j = 0, k = 0;

    while (i < mid && j < size - mid) {
        if (left[i] <= right[j]) {
            temp[k++] = left[i++];
        }
        else {
            temp[k++] = right[j++];
        }
    }

    while (i < mid) temp[k++] = left[i++];
    while (j < size - mid) temp[k++] = right[j++];

    for (int idx = 0; idx < size; ++idx) {
        arr[idx] = temp[idx];
    }
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