#include <iostream>
#include <string>
using namespace std;

struct Bank {

    int accNum;
    string Name;
    float Balance;


};

void updateBalance(Bank& account, float newBalance){
    account.Balance = newBalance;
}



int main() {
    Bank account;

    cout << "Введите номер счета: ";
    cin >> account.accNum;

    cout << "Введите имя владельца: ";
    cin.ignore();
    getline(cin, account.Name);

    cout << "Введите баланс: ";
    cin >> account.Balance;

    float newBalance;
    cout << "Введите новый баланс: ";
    cin >> newBalance;

    updateBalance(account, newBalance);

    cout << "Спасибо! Ваш счет: " << account.Name << ", " << account.accNum << ", " << account.Balance << endl;

    return 0;
}
