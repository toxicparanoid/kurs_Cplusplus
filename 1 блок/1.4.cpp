#include <iostream>

int main() {
    setlocale(LC_ALL, "RUS");

//----------------------------------------------------------
    std::cout << "1 Задание: " << std::endl;

    int val, summ = 0;

    do
    {
        std::cout << "Введите целое число или число '0', чтобы закончить: ";
        std::cin >> val;
        summ += val;

    } while (val != 0);
    std::cout << "Сумма: " << summ << std::endl << std::endl;
    
    




//----------------------------------------------------------
    std::cout << "2 Задание: " << std::endl;
    
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