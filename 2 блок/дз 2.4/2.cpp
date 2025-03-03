#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

class Address {
private:
    std::string city;
    std::string street;
    int houseNumber;
    int apartmentNumber;

public:
    Address(const std::string& city, const std::string& street, int houseNumber, int apartmentNumber)
        : city(city), street(street), houseNumber(houseNumber), apartmentNumber(apartmentNumber) {}

    std::string get_output_address() const {
        return city + ", " + street + ", " + std::to_string(houseNumber) + ", " + std::to_string(apartmentNumber);
    }

    std::string get_city() const {
        return city;
    }
};

void sort(Address** addresses, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (addresses[j]->get_city() > addresses[j + 1]->get_city()) {
                std::swap(addresses[j], addresses[j + 1]);
            }
        }
    }
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    std::ifstream inFile("in2.txt");
    std::ofstream outFile("out2.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    int N;
    inFile >> N;

    Address** addresses = new Address*[N];

    for (int i = 0; i < N; ++i) {
        std::string city, street;
        int houseNumber, apartmentNumber;

        inFile.ignore();
        std::getline(inFile, city);
        std::getline(inFile, street);
        inFile >> houseNumber;
        inFile >> apartmentNumber;

        addresses[i] = new Address(city, street, houseNumber, apartmentNumber);
    }

    sort(addresses, N);

    outFile << N << std::endl;

    for (int i = 0; i < N; ++i) {
        outFile << addresses[i]->get_output_address() << std::endl;
    }

    for (int i = 0; i < N; ++i) {
        delete addresses[i];
    }
    delete[] addresses;

    inFile.close();
    outFile.close();

    return 0;
}