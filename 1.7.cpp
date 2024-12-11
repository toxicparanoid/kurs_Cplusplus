#include<iostream>

void swap(int &x, int &y) {
    x = x + y;
    y = x - y;
    x = x - y;

    // int temp = x;
    // x = y;
    // y = temp;



}


int main() {
    setlocale(LC_ALL, "rus");
//--------------------------------------------------------------
	std::cout << "1 Задание: " << std::endl;


    int a = 2;
    short s = 2;
    long l = 2;
    long long ll = 2;
    float f = 5.003;
    double d = 5.00000003;
    long double ld = 0.002383432948;
    bool b = true;

    std::cout << "Int: " << &a << " " << sizeof(a) << std::endl;
    std::cout << "Short:  " << &s << " " << sizeof(s) << std::endl;
    std::cout << "Long: " << &l << " " << sizeof(l) << std::endl;
    std::cout << "Long long: " << &ll << " " << sizeof(ll) << std::endl;
    std::cout << "Float: " << &f << " " << sizeof(f) << std::endl;
    std::cout << "Double: " << &d << " " << sizeof(d) << std::endl;
    std::cout << "Long double: " << &ld << " " << sizeof(ld) << std::endl;
    std::cout << "Bool: " << &b << " " << sizeof(b) << std::endl << std::endl;

//--------------------------------------------------------------
	std::cout << "2 Задание: " << std::endl;

    int first = 5, second = 8;

    std::cout << "a = " << first << ", b = " << second << std::endl;

    swap(first, second);

    std::cout << "a = " << first << ", b = " << second << std::endl;
    std::cout << std::endl;


    return 0;
}