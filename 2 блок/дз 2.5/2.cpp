#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Figure {
protected:
    int sides;
    string name;
    vector<int> side_lengths;
    vector<int> angles;

public:
    Figure(int sides, const string& name, const vector<int>& side_lengths, const vector<int>& angles)
        : sides(sides), name(name), side_lengths(side_lengths), angles(angles) {}

    void print_info() const {
        cout << name << ":" << endl;
        cout << "Стороны: ";
        for (size_t i = 0; i < side_lengths.size(); ++i) {
            cout << (char)('a' + i) << "=" << side_lengths[i] << " ";
        }
        cout << endl;

        cout << "Углы: ";
        for (size_t i = 0; i < angles.size(); ++i) {
            cout << (char)('A' + i) << "=" << angles[i] << " ";
        }
        cout << endl << endl;
    }
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C) : Figure(3, "Треугольник", {a, b, c}, {A, B, C}) {}
};

class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c, int A, int B)
        : Triangle(a, b, c, A, B, 90) {
        name = "Прямоугольный треугольник";
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b, int A, int B)
        : Triangle(a, b, a, A, B, A) {
        name = "Равнобедренный треугольник";
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int a)
        : Triangle(a, a, a, 60, 60, 60) {
        name = "Равносторонний треугольник";
    }
};

class Quadrangle : public Figure {
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
        : Figure(4, "Четырехугольник", {a, b, c, d}, {A, B, C, D}) {}
};

class Rectangle : public Quadrangle {
public:
    Rectangle(int a, int b)
        : Quadrangle(a, b, a, b, 90, 90, 90, 90) {
        name = "Прямоугольник";
    }
};

class Square : public Quadrangle {
public:
    Square(int a)
        : Quadrangle(a, a, a, a, 90, 90, 90, 90) {
        name = "Квадрат";
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B)
        : Quadrangle(a, b, a, b, A, B, A, B) {
        name = "Параллелограмм";
    }
};

class Rhombus : public Quadrangle {
public:
    Rhombus(int a, int A, int B)
        : Quadrangle(a, a, a, a, A, B, A, B) {
        name = "Ромб";
    }
};

int main() {
    Triangle triangle(10, 20, 30, 50, 60, 70);
    RightTriangle rightTriangle(10, 20, 30, 50, 60);
    IsoscelesTriangle isoscelesTriangle(10, 20, 50, 60);
    EquilateralTriangle equilateralTriangle(30);
    Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle(10, 20);
    Square square(20);
    Parallelogram parallelogram(20, 30, 30, 40);
    Rhombus rhombus(30, 30, 40);

    triangle.print_info();
    rightTriangle.print_info();
    isoscelesTriangle.print_info();
    equilateralTriangle.print_info();
    quadrangle.print_info();
    rectangle.print_info();
    square.print_info();
    parallelogram.print_info();
    rhombus.print_info();

    return 0;
}