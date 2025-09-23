#include "func.h"
#include <cmath>
#include <iostream>

using namespace std;

const double EPSILON = 1e-5;

// Вспомогательная функция для сравнения double с учетом погрешности
bool areEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

// Функции для точки
void readPoint(Point& p) {
    cin >> p.x >> p.y;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

// Функции для круга
void readCircle(Circle& c) {
    readPoint(c.center);
    cin >> c.radius;
}

void printCircle(const Circle& c) {
    cout << "Circle: center ";
    printPoint(c.center);
    cout << ", radius " << c.radius;
}

double circleCircumference(const Circle& c) {
    return 2 * M_PI * c.radius;
}

double circleArea(const Circle& c) {
    return M_PI * c.radius * c.radius;
}

// Функции для квадрата
void readSquare(Square& s) {
    readPoint(s.topLeft);
    cin >> s.side;
}

void printSquare(const Square& s) {
    cout << "Square: top-left ";
    printPoint(s.topLeft);
    cout << ", side " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

// Проверка принадлежности точки кругу (строго внутри)
bool isPointInsideCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    double distanceSquared = dx * dx + dy * dy;
    return distanceSquared < c.radius * c.radius - EPSILON;
}

// Проверка принадлежности точки квадрату (строго внутри)
bool isPointInsideSquare(const Point& p, const Square& s) {
    return p.x > s.topLeft.x + EPSILON && 
           p.x < s.topLeft.x + s.side - EPSILON &&
           p.y < s.topLeft.y - EPSILON && 
           p.y > s.topLeft.y - s.side + EPSILON;
}

// Проверка нахождения точки на круге
bool isPointOnCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    double distanceSquared = dx * dx + dy * dy;
    double radiusSquared = c.radius * c.radius;
    return fabs(distanceSquared - radiusSquared) < EPSILON;
}

// Проверка нахождения точки на квадрате
bool isPointOnSquare(const Point& p, const Square& s) {
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    // Проверка на вертикальных границах
    bool onVertical = (fabs(p.x - left) < EPSILON || fabs(p.x - right) < EPSILON) &&
                      p.y <= top + EPSILON && p.y >= bottom - EPSILON;
    
    // Проверка на горизонтальных границах
    bool onHorizontal = (fabs(p.y - top) < EPSILON || fabs(p.y - bottom) < EPSILON) &&
                        p.x >= left - EPSILON && p.x <= right + EPSILON;
    
    return onVertical || onHorizontal;
}

// Проверка пересечения двух кругов
bool circlesIntersect(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double distance = sqrt(dx * dx + dy * dy);
    double sumRadii = c1.radius + c2.radius;
    double diffRadii = fabs(c1.radius - c2.radius);
    
    return distance <= sumRadii + EPSILON && distance >= diffRadii - EPSILON;
}

// Проверка пересечения двух квадратов
bool squaresIntersect(const Square& s1, const Square& s2) {
    double left1 = s1.topLeft.x;
    double right1 = s1.topLeft.x + s1.side;
    double top1 = s1.topLeft.y;
    double bottom1 = s1.topLeft.y - s1.side;
    
    double left2 = s2.topLeft.x;
    double right2 = s2.topLeft.x + s2.side;
    double top2 = s2.topLeft.y;
    double bottom2 = s2.topLeft.y - s2.side;
    
    return !(right1 < left2 - EPSILON || left1 > right2 + EPSILON ||
             bottom1 > top2 + EPSILON || top1 < bottom2 - EPSILON);
}

// Проверка пересечения круга и квадрата
bool circleSquareIntersect(const Circle& c, const Square& s) {
    // Находим ближайшую точку квадрата к центру круга
    double closestX = max(s.topLeft.x, min(c.center.x, s.topLeft.x + s.side));
    double closestY = max(s.topLeft.y - s.side, min(c.center.y, s.topLeft.y));
    
    // Проверяем расстояние от центра круга до ближайшей точки квадрата
    double dx = c.center.x - closestX;
    double dy = c.center.y - closestY;
    double distanceSquared = dx * dx + dy * dy;
    
    return distanceSquared <= c.radius * c.radius + EPSILON;
}

// Проверка принадлежности круга кругу
bool isCircleInsideCircle(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double distance = sqrt(dx * dx + dy * dy);
    return distance + c1.radius <= c2.radius + EPSILON;
}

// Проверка принадлежности квадрата квадрату
bool isSquareInsideSquare(const Square& s1, const Square& s2) {
    double left1 = s1.topLeft.x;
    double right1 = s1.topLeft.x + s1.side;
    double top1 = s1.topLeft.y;
    double bottom1 = s1.topLeft.y - s1.side;
    
    double left2 = s2.topLeft.x;
    double right2 = s2.topLeft.x + s2.side;
    double top2 = s2.topLeft.y;
    double bottom2 = s2.topLeft.y - s2.side;
    
    return left1 >= left2 - EPSILON && right1 <= right2 + EPSILON &&
           top1 <= top2 + EPSILON && bottom1 >= bottom2 - EPSILON;
}

// Проверка принадлежности квадрата кругу
bool isSquareInsideCircle(const Square& s, const Circle& c) {
    // Проверяем все вершины квадрата
    Point vertices[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };
    
    for (int i = 0; i < 4; i++) {
        if (!isPointInsideCircle(vertices[i], c)) {
            return false;
        }
    }
    return true;
}

// Проверка принадлежности круга квадрату
bool isCircleInsideSquare(const Circle& c, const Square& s) {
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    return c.center.x - c.radius >= left - EPSILON &&
           c.center.x + c.radius <= right + EPSILON &&
           c.center.y + c.radius <= top + EPSILON &&
           c.center.y - c.radius >= bottom - EPSILON;
}