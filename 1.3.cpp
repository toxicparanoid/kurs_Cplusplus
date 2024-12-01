#include <iostream>


std::string numberToWords(int n) {
    const std::string units[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    const std::string teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    const std::string tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};

    if (n < 0) return "минус " + numberToWords(-n);
    if (n < 10) return units[n];
    if (n < 20) return teens[n - 10];
    if (n < 100) return tens[n / 10] + (n % 10 != 0 ? " " + units[n % 10] : "");

    return "";
}



int main() {
    setlocale(LC_ALL, "rus");
 /*   std::cout << "1 Задание:" << "\n";
    std::cout << "A\tB\tA || B\tA && B" << std::endl;

    for (bool A : {false, true}) {
        for (bool B : {false, true}) {
            std::cout << (A ? "true" : "false") << "\t" << (B ? "true" : "false") << "\t";

            if (A || B) {
                std::cout << "true\t";
            } else {
                std::cout << "false\t";
            }

            if (A && B) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        }
    }

//-----------------------------------------------------------------------------

    std::cout << "\n\n" << "2 Задание:" << "\n";

    int first, second, third;
    std::cout << "Введите первое чилсло: ";
    std::cin >> first;
    std::cout << "Введите второе чилсло: ";
    std::cin >> second;
    std::cout << "Введите третье чилсло: ";
    std::cin >> third;

    int max = (first > second) ? ((first > third) ? first : third) : ((second > third) ? second : third);

    int mid = (first < second) ? ((first > third) ? first : (second > third) ? third : second) : ((second > third) ? second : (first > third) ? third : first);

    int min = (first < second) ? ((first < third) ? first : third) : ((second < third) ? second : third);
    
    std::cout << "Результат: " << max << " " << mid << " " << min << std::endl;

//-----------------------------------------------------------------------------

    std::cout << "\n\n" << "3 Задание:" << "\n";

    std::string sx, sign;
    int age;
    std::cout << "Введите пол: ";
    std::cin >> sx;
    std::cout << "Введите знак зодиака: ";
    std::cin >> sign;
    std::cout << "Введите возраст: ";
    std::cin >> age;

    if (sx == "м" && (sign == "рак" || sign == "рыбы" || sign == "скорпион") && (age < 40))
    {
        std::cout << "Сегодня очень плодотворный день. Можно добиться того, что прежде казалось почти невозможным." << std::endl;
    } else if (sx == "ж" && (sign == "телец" || sign == "дева" || sign == "козерог") && (15 <= age <= 30))
    {
        std::cout << "Сегодняшний вечер подходит для общения с друзьями, проведения домашних праздников и импровизированных вечеринок. Будет не только весело, но и интересно: найдётся дело, которое увлечёт всех.";

    } else {
        std::cout << "Гороскоп для вас находится в разработке. Приходите чуточку позже ;)";
    }*/

//-----------------------------------------------------------------------------

    int num1, num2;

    std::cout << "Введите целое число: ";
    std::cin >> num1;
    std::cout << "Введите целое число: ";
    std::cin >> num2;

    if (num1 < -100 || num1 >= 100 || num2 < -100 || num2 >= 100) {
        std::cout << "Ошибка: числа должны быть в диапазоне от -100 до 100." << std::endl;
        return 1;
    }

    if (num1 < num2) {
        std::cout << numberToWords(num1) << " меньше чем " << numberToWords(num2) << std::endl;
    } else if (num1 > num2) {
        std::cout << numberToWords(num1) << " больше чем " << numberToWords(num2) << std::endl;
    } else {
        std::cout << numberToWords(num1) << " равно " << numberToWords(num2) << std::endl;
    }



    return 0;
}


// ураа оно сработало, ща еще раз проверю
