#include <iostream>

void counting_function(){
}

namespace add {
    int calc(int x, int y) {
        return x + y;
    }
}

namespace subtract {
    int calc(int x, int y) {
        return x - y;
    }
}

namespace multiply {
    int calc(int x, int y) {
        return x * y;
    }
}

namespace divide {
    int calc(int x, int y) {
        if (y == 0) {
            std::cout << "Ошибка: деление на ноль!" << std::endl;
            return 0;
        }
        return x / y;
    }
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "rus");
    std::cout << "1 Задание: " << std::endl;

    int cnt = 0;
    for (int i = 0; i < 15; i++)
    {
        counting_function();
        cnt += 1;
        std::cout << "Количество вызовов функции counting_function(): " << cnt << std::endl;

    }
    
    std::cout << std::endl;

//------------------------------------------------------------------------------------------
    std::cout << "2 Задание: " << std::endl;

    int x, y;

    std::cout << "Введите числа х и у: ";

    std::cin >> x >> y;

    std::cout << "х = " << x << ", у = " << y << std::endl;

    std::cout << "Сложение: " << add::calc(x, y) << std::endl;
    std::cout << "Вычитание: " << subtract::calc(x, y) << std::endl;
    std::cout << "Умножение: " << multiply::calc(x, y) << std::endl;
    std::cout << "Деление: " << divide::calc(x, y) << std::endl;

    return 0;
}