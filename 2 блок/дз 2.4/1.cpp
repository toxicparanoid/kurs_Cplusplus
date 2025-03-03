#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

class Address {
private:
    string city;
    string street;
    int houseNumber;
    int apartmentNumber;

public:
    Address(const string& city, const string& street, int houseNumber, int apartmentNumber)
        : city(city), street(street), houseNumber(houseNumber), apartmentNumber(apartmentNumber) {}

    string get_output_address() const {
        return city + ", " + street + ", " + to_string(houseNumber) + ", " + to_string(apartmentNumber);
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    ifstream inFile("in1.txt");
    ofstream outFile("out1.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    int N;
    inFile >> N;

    Address** addresses = new Address*[N];

    for (int i = 0; i < N; ++i) {
        string city, street;
        int houseNumber, apartmentNumber;

        inFile.ignore();
        getline(inFile, city);
        getline(inFile, street);
        inFile >> houseNumber;
        inFile >> apartmentNumber;

        addresses[i] = new Address(city, street, houseNumber, apartmentNumber);
    }

    outFile << N << endl;

    for (int i = N - 1; i >= 0; --i) {
        outFile << addresses[i]->get_output_address() << endl;
    }

    for (int i = 0; i < N; ++i) {
        delete addresses[i];
    }
    delete[] addresses;

    inFile.close();
    outFile.close();

    return 0;
}