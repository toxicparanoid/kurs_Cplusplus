#include<iostream>

int sum(int a, int b)
{
    int l = a + b;
    return l;
}

int diff(int a, int b)
{
    int l = a - b;
    return l;
}

int multiplication(int a, int b)
{
    int l = a * b;
    return l;
}

double division(double a, double b)
{
    double l = a / b;
    return l;
}

int qu(int x, int y){
	int res = 1;
	for (int i = 0; i < y; i++){
		res *= x;
	}
	return res;

}

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}



int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
//--------------------------------------------------------------
	std::cout << "1 Задание: " << std::endl;

	int a = 5, b = 10;

	int s = sum(a, b);
	int dif = diff(a, b);
	int mult = multiplication(a, b);
	double div = division(a, b);

	std::cout << a << " + " << b << " = " << s << std::endl;
	std::cout << a << " - " << b << " = " << dif << std::endl;
	std::cout << a << " * " << b << " = " << mult << std::endl;
	std::cout << a << " / " << b << " = " << div << std::endl;
	std::cout << std::endl;

//--------------------------------------------------------------
	std::cout << "2 Задание: " << std::endl;

	int fis = 5, sec = 2;

	std::cout << fis << " в степени " << sec << " = " << qu(fis, sec) << std::endl;

	fis = 3, sec = 3;

	std::cout << fis << " в степени " << sec << " = " << qu(fis, sec) << std::endl;

	fis = 4, sec = 4;

	std::cout << fis << " в степени " << sec << " = " << qu(fis, sec) << std::endl;

	fis = 2, sec = 3;

	std::cout << "Доп. вариант: \n" << fis << " в степени " << sec << " = " << qu(fis, sec) << std::endl;
	std::cout << std::endl;

//--------------------------------------------------------------
	std::cout << "3 Задание: " << std::endl;

	int chisfib;

	std::cout << "Введите число: ";
	std::cin >> chisfib;

	std::cout << "Числа Фибоначчи: ";

	for (int i = 0; i < chisfib; i++) {
        std::cout << fibonacci(i) << " ";
    }
    std::cout << std::endl;
	


	return 0;
}