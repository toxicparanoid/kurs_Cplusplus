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
public:
    Quadrangle() {
        sides = 4;
        name = "Четырехугольник: ";
    }
};



int main() {
    Figure figur;
    Triangle treug;
    Quadrangle quadr;

    cout << "Количество сторон:" << endl;

    figur.get_name();
    figur.get_sides_count();
    cout << endl;

    treug.get_name();
    treug.get_sides_count();
    cout << endl;

    quadr.get_name();
    quadr.get_sides_count();
    cout << endl;

    return 0;
}