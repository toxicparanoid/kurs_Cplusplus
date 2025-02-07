#include <iostream>
#include <fstream>

void calc(float x, float y, char z){
    if (z == '+') {
        std::cout << "Сумма чисел: " << x + y << std::endl;
    } else if (z == '-') {
        std::cout << "Разность чисел: " << x - y << std::endl;
    } else if (z == '*') {
        std::cout << "Произведение чисел: " << x * y << std::endl;
    } else if (z == '/') {
        std::cout << "Частное чисел: " << x / y << std::endl;
    } else {
        std::cout << "Неправильно введено выражение!" << std::endl;
    }
} 

int main() {

    float a, b;
    char c;

    std::cout << "Введите два числа и операцию: " << std::endl;
    std::cin >> a >> b >> c;
    calc(a, b, c);




    return 0;
}