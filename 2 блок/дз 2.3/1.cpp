#include <iostream>
using namespace std;

class Calculator {
private:
    double num1;
    double num2;

public:
    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        } else {
            return false;
        }
    }

    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        } else {
            return false;
        }
    }

    double add() {
        return num1 + num2;
    }

    double multiply() {
        return num1 * num2;
    }

    double subtract_1_2() {
        return num1 - num2;
    }

    double subtract_2_1() {
        return num2 - num1;
    }

    double divide_1_2() {
        return num1 / num2;
    }

    double divide_2_1() {
        return num2 / num1;
    }
};

int main() {
    Calculator calc;
    double num1, num2;

    while (true) {
        cout << "Введите num1: ";
        cin >> num1;
        while (!calc.set_num1(num1)) {
            cout << "Неверный ввод! Введите num1: ";
            cin >> num1;
        }

        cout << "Введите num2: ";
        cin >> num2;
        cout << endl;
        while (!calc.set_num2(num2)) {
            cout << "Неверный ввод! Введите num2: ";
            cin >> num2;
        }

        cout << "num1 + num2 = " << calc.add() << endl;
        cout << "num1 * num2 = " << calc.multiply() << endl;
        cout << "num1 - num2 = " << calc.subtract_1_2() << endl;
        cout << "num2 - num1 = " << calc.subtract_2_1() << endl;
        cout << "num1 / num2 = " << calc.divide_1_2() << endl;
        cout << "num2 / num1 = " << calc.divide_2_1() << endl;

        cout << "-------------------------" << endl;
    }

    return 0;
}