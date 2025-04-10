#include <iostream>
using namespace std;


int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {

    int n, fib;
    cout << "Введите число: ";
    cin >> n;

    cout << "Числа Фибоначчи: ";

    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }

    cout << endl;

    return 0;
}

//слжность алгоритма - O(2^n), потому что внутри можно сказать реализовано дерево рекурсии, так как при каждом вызове fibonacci
//вызываются еще две рекурсии. Сложность по памяти - O(n).