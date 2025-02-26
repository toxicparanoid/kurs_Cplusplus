#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
};

int main() {
    std::ifstream inFile("in1.txt");
    std::ofstream outFile("task1.txt");

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

    outFile << N << std::endl;

    for (int i = N - 1; i >= 0; --i) {
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