#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

// Функции для точки
void readPoint(Point& p);
void printPoint(const Point& p);

// Функции для круга
void readCircle(Circle& c);
void printCircle(const Circle& c);
double circleCircumference(const Circle& c);
double circleArea(const Circle& c);

// Функции для квадрата
void readSquare(Square& s);
void printSquare(const Square& s);
double squarePerimeter(const Square& s);
double squareArea(const Square& s);

// Проверка принадлежности точки фигуре (строго внутри)
bool isPointInsideCircle(const Point& p, const Circle& c);
bool isPointInsideSquare(const Point& p, const Square& s);

// Проверка нахождения точки на контуре
bool isPointOnCircle(const Point& p, const Circle& c);
bool isPointOnSquare(const Point& p, const Square& s);

// Проверка пересечения фигур
bool circlesIntersect(const Circle& c1, const Circle& c2);
bool squaresIntersect(const Square& s1, const Square& s2);
bool circleSquareIntersect(const Circle& c, const Square& s);

// Проверка принадлежности фигур (первая внутри второй)
bool isCircleInsideCircle(const Circle& c1, const Circle& c2);
bool isSquareInsideSquare(const Square& s1, const Square& s2);
bool isSquareInsideCircle(const Square& s, const Circle& c);
bool isCircleInsideSquare(const Circle& c, const Square& s);

#endif