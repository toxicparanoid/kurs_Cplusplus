#include <iostream>
#include <string>

using namespace std;

int main() {

    string name, surname;

    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите фамилию: ";
    cin >> surname;
    cout << "Здарова, " << name + " " + surname << "!\n";

    return 0;
}