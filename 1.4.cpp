#include <iostream>

int main() {
    setlocale(LC_ALL, "RUS");
    int number;
    int sum = 0;

    std::cout << "Введите целое число: ";
    std::cin >> number;

    while (number > 0) {
        sum += number % 10;
        number /= 10; 
    }

    std::cout << "Сумма цифр: " << sum << std::endl;
    
    return 0;
}