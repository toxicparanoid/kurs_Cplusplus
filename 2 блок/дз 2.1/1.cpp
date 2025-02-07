#include <iostream>
#include <string>

using namespace std;

enum Month {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

string getMonthName(Month month) {
    switch (month) {
        case JANUARY:   return "Январь";
        case FEBRUARY:  return "Февраль";
        case MARCH:     return "Март";
        case APRIL:     return "Апрель";
        case MAY:       return "Май";
        case JUNE:      return "Июнь";
        case JULY:      return "Июль";
        case AUGUST:    return "Август";
        case SEPTEMBER: return "Сентябрь";
        case OCTOBER:   return "Октябрь";
        case NOVEMBER:  return "Ноябрь";
        case DECEMBER:  return "Декабрь";
        default:        return "Неправильный номер!";
    }
}

int main() {
    int monthNumber;

    while (true) {
        cout << "Введите номер месяца: ";
        cin >> monthNumber;

        if (monthNumber == 0) {
            cout << "До свидания" << endl;
            break;
        }

        Month month = static_cast<Month>(monthNumber);

        string monthName = getMonthName(month);
        cout << monthName << endl;
    }

    return 0;
}