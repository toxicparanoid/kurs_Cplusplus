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

int qu(int x, int y) {
	int result = 1;
	for (int i = 0; i < y; i++)
	{
		result *= y;
	}
	return result;
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

	std::cout << 5 << "в степени " << 2 << " = " << qu(5, 2) << std::endl;


	return 0;
}