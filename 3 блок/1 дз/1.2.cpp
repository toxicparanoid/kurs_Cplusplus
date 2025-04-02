//сложность алгоритма O(logn), так как здесь реализован бинарный поиск
#include <iostream>
using namespace std;

int count(int* arr, int size, int s) {
    int left = 0;
    int right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > s) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return size - left;
}

int main() {

    int s, size = 9;
    int arr[size] = {14, 16, 19, 32, 32, 32, 56, 69, 72};

    cout << "Введите точку отсчета: ";
    cin >> s;

    cout << "Количество элементов в массиве больших, чем " << s << ": " << count(arr, size, s) << endl;

    return 0;
}