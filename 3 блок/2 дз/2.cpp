#include <iostream>
#include <vector>
using namespace std;


int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
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