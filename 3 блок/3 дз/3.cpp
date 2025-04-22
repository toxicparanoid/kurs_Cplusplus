#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void merge_sort(int* arr, int size) {
    if (size == 0) return;

    int max_val = *max_element(arr, arr + size);
    vector<int> count(max_val + 1, 0);

    for (int i = 0; i < size; ++i) {
        count[arr[i]]++;
    }

    int index = 0;
    for (int val = 0; val <= max_val; ++val) {
        while (count[val] > 0) {
            arr[index++] = val;
            count[val]--;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    
    int arr[] = { 21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17, 13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10, };

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