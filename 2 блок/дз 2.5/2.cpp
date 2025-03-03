#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Figure {
protected:
    int sides;
    string name;

public:
    Figure() {
        sides = 0;
        name = "Фигура: ";
    }
    void get_sides_count() {
        cout << sides;
    }

    void get_name() {
        cout << name;
    }
};

class Triangle : public Figure {
public:
    Triangle(){
        sides = 3;
        name = "Треугольник: ";
    }
};

class Quadrangle : public Figure {
protected:
    int a, b, c, d, A, B, C, D;
public:
    Quadrangle() {
        sides = 4;
        name = "Четырехугольник: ";
    }

    void get_par() {
        cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;
        cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << endl;
    }

};

class Parallelogram : public Quadrangle {
    public:
        Parallelogram() {
            name = "Параллелограмм:\n";
            a = c = 20;
            b = d = 30;
            A = C = 30;
            B = D = 40;
        }
    };

class Romb : public Parallelogram {
public:
    Romb() {
        name = "Ромб:\n";
        a = c = b = d = 30;
        A = C = 30;
        B = D = 40;
    }
};



int main() {
    Parallelogram par;

    par.get_name();
    par.get_par();

    return 0;
}