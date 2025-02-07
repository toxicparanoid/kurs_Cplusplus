#include <iostream>
#include <string>
using namespace std;

struct Adress {
    string City;
    string Street;
    int HouseNumber;
    int ApartNumber;
    int Index;
};

void Propiska(Adress& adres) {
    cout << "Город: " << adres.City << endl;
    cout << "Улица: " << adres.Street << endl;
    cout << "Номер дома: " << adres.HouseNumber << endl;
    cout << "Номер квартиры: " << adres.ApartNumber << endl;
    cout << "Индекс: " << adres.Index << endl;
    cout << "-----------------------------------" << endl;
}

int main() {

    Adress adres1 = {"Москва", "Арбат", 12, 8, 12345};
    Adress adres2 = {"Ижевск", "Пушкина", 59, 143, 953769};

    Propiska(adres1);
    Propiska(adres2);

    return 0;
}