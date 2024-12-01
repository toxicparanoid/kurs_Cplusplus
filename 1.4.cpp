#include<iostream>

int main() {
    setlocale(LC_ALL, "rus");

    int a, b, c, d, e;

    std::cout << "Введите целое число: ";
    std::cin >> a;
    while(true){

        if (a == 0) {
            std::cout << "До свидания!" << std::endl;
          break;
        }

        if (a > 999) {
            b = a / 1000;
            c = a / 100 % 10;
            d = a / 10 % 10;
            e = a % 10;
            std:: cout << "Сумма цифр: " << (b + c + d + e) << std::endl;
            break;
        }

        if (a > 99) {
            b = a / 100;
            c = a / 10 % 10;
            d = a % 10;
            std:: cout << "Сумма цифр: " << (b + c + d) << std::endl;
            break;
        }

        if (a > 9) {
            b = a / 10;
            c = a % 10;
            std:: cout << "Сумма цифр: " << (b + c) << std::endl;
            break;
        }

        if (a < 10) {
            std::cout << "Сумма цифр: " << a << std::endl;
            break;
        }
    }
    return 0;
}