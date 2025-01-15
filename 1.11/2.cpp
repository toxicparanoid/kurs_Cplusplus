#include <iostream>
#include <string>

using namespace std;

int main() {

    string ans;

    while (true) {
        cout << "Ну давай, попробуй угадать слово: ";
        getline(cin, ans);
        if (ans == "малина") {
            cout << "Мои поздравления, ты победил! Загаданное слово - малина" << endl;
            break;
        } else 
            cout << "Неправильно, давай еще раз!" << endl;
            continue;
    }

    return 0;
}