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

    virtual bool check() const {
        return sides == 0;
    }

    virtual void print_info() const {
        cout << name << ":" << endl;
        cout << (check() ? "Правильная" : "Неправильная") << endl;
        cout << "Количество сторон: " << sides << endl;
    }
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C)
        : Figure(3, "Треугольник", {a, b, c}, {A, B, C}) {}

    bool check() const override {
        int sum_angles = 0;
        for (int angle : angles) {
            sum_angles += angle;
        }
        return sum_angles == 180 && sides == 3;
    }

    void print_info() const override {
        Figure::print_info();
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

class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c, int A, int B)
        : Triangle(a, b, c, A, B, 90) {
        name = "Прямоугольный треугольник";
    }

    bool check() const override {
        return Triangle::check() && angles[2] == 90;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(int a, int b, int A, int B)
        : Triangle(a, b, a, A, B, A) {
        name = "Равнобедренный треугольник";
    }

    bool check() const override {
        return Triangle::check() && side_lengths[0] == side_lengths[2] && angles[0] == angles[2];
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(int a)
        : Triangle(a, a, a, 60, 60, 60) {
        name = "Равносторонний треугольник";
    }

    bool check() const override {
        return Triangle::check() && side_lengths[0] == side_lengths[1] && side_lengths[1] == side_lengths[2] &&
               angles[0] == 60 && angles[1] == 60 && angles[2] == 60;
    }
};

class Quadrangle : public Figure {
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
        : Figure(4, "Четырехугольник", {a, b, c, d}, {A, B, C, D}) {}

    bool check() const override {
        int sum_angles = 0;
        for (int angle : angles) {
            sum_angles += angle;
        }
        return sum_angles == 360 && sides == 4;
    }

    void print_info() const override {
        Figure::print_info();
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

class Rectangle : public Quadrangle {
public:
    Rectangle(int a, int b)
        : Quadrangle(a, b, a, b, 90, 90, 90, 90) {
        name = "Прямоугольник";
    }

    bool check() const override {
        return Quadrangle::check() && side_lengths[0] == side_lengths[2] && side_lengths[1] == side_lengths[3] &&
               angles[0] == 90 && angles[1] == 90 && angles[2] == 90 && angles[3] == 90;
    }
};

class Square : public Quadrangle {
public:
    Square(int a)
        : Quadrangle(a, a, a, a, 90, 90, 90, 90) {
        name = "Квадрат";
    }

    bool check() const override {
        return Quadrangle::check() && side_lengths[0] == side_lengths[1] && side_lengths[1] == side_lengths[2] &&
               side_lengths[2] == side_lengths[3] && angles[0] == 90 && angles[1] == 90 && angles[2] == 90 && angles[3] == 90;
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(int a, int b, int A, int B)
        : Quadrangle(a, b, a, b, A, B, A, B) {
        name = "Параллелограмм";
    }

    bool check() const override {
        return Quadrangle::check() && side_lengths[0] == side_lengths[2] && side_lengths[1] == side_lengths[3] &&
               angles[0] == angles[2] && angles[1] == angles[3];
    }
};

class Rhombus : public Quadrangle {
public:
    Rhombus(int a, int A, int B)
        : Quadrangle(a, a, a, a, A, B, A, B) {
        name = "Ромб";
    }

    bool check() const override {
        return Quadrangle::check() && side_lengths[0] == side_lengths[1] && side_lengths[1] == side_lengths[2] &&
               side_lengths[2] == side_lengths[3] && angles[0] == angles[2] && angles[1] == angles[3];
    }
};

int main() {
    Figure figure(0, "Фигура", {}, {});
    Triangle triangle(10, 20, 30, 50, 60, 70);
    RightTriangle rightTriangle1(10, 20, 30, 50, 60);
    RightTriangle rightTriangle2(10, 20, 30, 50, 40);
    IsoscelesTriangle isoscelesTriangle(10, 20, 50, 60);
    EquilateralTriangle equilateralTriangle(30);
    Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle rectangle(10, 20);
    Square square(20);
    Parallelogram parallelogram(20, 30, 30, 40);
    Rhombus rhombus(30, 30, 40);

    figure.print_info();
    triangle.print_info();
    rightTriangle1.print_info();
    rightTriangle2.print_info();
    isoscelesTriangle.print_info();
    equilateralTriangle.print_info();
    quadrangle.print_info();
    rectangle.print_info();
    square.print_info();
    parallelogram.print_info();
    rhombus.print_info();

    return 0;
}