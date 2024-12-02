#include <iostream>

int main() {
//----------------------------------------------------------
    std::cout << "2 Задание: " << std::endl;
    
    setlocale(LC_ALL, "RUS");
    int number;
    int sum = 0;

    std::cout << "Введите целое число: ";
    std::cin >> number;

    while (number > 0) {
        sum += number % 10;
        number /= 10; 
    }

    std::cout << "Сумма цифр: " << sum << std::endl << std::endl;

//----------------------------------------------------------
    std::cout << "3 Задание: " << std::endl;

    int value, ans;

    std::cout << "Введите целое число: ";
    std::cin >> value;

    for (int i = 1; i < 11; i++) {
        ans = value * i;
        std::cout << value << " x " << i << " = " << ans << std::endl;
    }





    return 0;
}