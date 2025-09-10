#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14;

struct Point {
    double x;
    double y;

    void set_point(double x_p, double y_p) {
        x = x_p;
        y = y_p;
    }

    void get_point() {
        cout << "x точки: " << x << endl;
        cout << "y точки: " << y << endl;
    }
};

struct Circle {
    Point centre;
    double radius;

    void set_circle(double x_c, double y_c, double radius_c) {
        centre.set_point(x_c, y_c);
        radius = radius_c;
    }

    void get_circle() {
        cout << "центр круга: (" << centre.x << ", " << centre.y << ")" << endl;
        cout << "радиус круга: " << radius << endl;
    }

    double len_circle() {
        return 2 * PI * radius;
    }

    double square_circle() {
        return PI * radius * radius;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Point point;
    Circle circle;

    double x_p, y_p, x_c, y_c, radius_c;

    cout << "Введите координаты точки(x y): ";
    cin >> x_p >> y_p;

    cout << "Введите координаты центра круга(x y): ";
    cin >> x_c >> y_c;

    cout << "Введите радиус круга: ";
    cin >> radius_c;

    point.set_point(x_p, y_p);
    cout << "Точка:" << endl;
    point.get_point();
    cout << endl;

    circle.set_circle(x_c, y_c, radius_c);
    cout << "Круг:" << endl;
    circle.get_circle();

    cout << "Длина окружности: " << circle.len_circle() << endl;
    cout << "Площадь круга: " << circle.square_circle() << endl;

    return 0;
}