#include "1.h"

int main() {

    int first;
    int second;
    int operation;

    cout << "Введите первое число: ";
    cin >> first;
    cout << "Введите второе число: ";
    cin >> second;

    while (true) {
        cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
        cin >> operation;

        switch (operation) {
        case 1:
            sm(first, second);
            break;
        case 2:
            mins(first, second);
            break;
        case 3:
            umn(first, second);
            break;
        case 4:
            del(first, second);
            break;
        case 5:
            step(first, second);
            break;
        default:
            cout << "Такого выбора не существует. Повторите попытку!" << endl;
            continue;
        }
    }
    
    return 0;
}