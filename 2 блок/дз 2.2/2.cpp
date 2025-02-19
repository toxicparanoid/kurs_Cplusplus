#include <iostream>
#include <string>
using namespace std;

class Counter {
    private:
    int cnt;

    public:

    Counter() {
        cnt = 1;
    }

    Counter(int initialCnt) {
        cnt = initialCnt;
    }

    void plus() {
        cnt++;
    }

    void minus() {
        cnt--;
    }

    int getCnt() const {
        return cnt;
    }
};

int main() {

    int initialValue = 1;
    char choice;
    char command;

    cout << "Вы хотите указать начальное значение счётчика? (Введите y или n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        cout << "Введите начальное значение счётчика: ";
        cin >> initialValue;
    }
    
    Counter counter(initialValue);


    while (true) {

        cout << "Введите команду ('+', '-', '=' или 'x'): " << endl;
        cin >> command;

        switch (command) {

            case '+':
                counter.plus();
                break;

            case '-':
                counter.minus();
                break;

            case '=':
                cout << "Текущее значение: " << counter.getCnt() << endl;
                break;

            case 'x':
                cout << "До свидания!" << endl;
                return 0;

            default:
                cout << "Неизвестная команда. Давай по новой Миша." << endl;
                break;

        }
    }
    return 0;
}
