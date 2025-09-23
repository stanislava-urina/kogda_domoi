#ifndef STRUCTS_H
#define STRUCTS_H

// Структура для точки
struct Point {
    double x;
    double y;
};

// Структура для круга
struct Circle {
    Point center;
    double radius;
};

// Структура для квадрата
struct Square {
    Point topLeft;
    double side;
};

#endif