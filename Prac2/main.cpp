#include <iostream>
#include "func.h"

using namespace std;

void demonstratePoint() {
    cout << "=== Point Demonstration ===" << endl;
    Point p;
    cout << "Enter point coordinates (x y): ";
    readPoint(p);
    cout << "Point: ";
    printPoint(p);
    cout << endl << endl;
}

void demonstrateCircle() {
    cout << "=== Circle Demonstration ===" << endl;
    Circle c;
    cout << "Enter circle (center_x center_y radius): ";
    readCircle(c);
    printCircle(c);
    cout << endl;
    cout << "Circumference: " << circleCircumference(c) << endl;
    cout << "Area: " << circleArea(c) << endl << endl;
}

void demonstrateSquare() {
    cout << "=== Square Demonstration ===" << endl;
    Square s;
    cout << "Enter square (topLeft_x topLeft_y side): ";
    readSquare(s);
    printSquare(s);
    cout << endl;
    cout << "Perimeter: " << squarePerimeter(s) << endl;
    cout << "Area: " << squareArea(s) << endl << endl;
}

void demonstratePointInFigures() {
    cout << "=== Point in Figures Demonstration ===" << endl;
    Point p;
    Circle c;
    Square s;
    
    cout << "Enter point coordinates (x y): ";
    readPoint(p);
    cout << "Enter circle (center_x center_y radius): ";
    readCircle(c);
    cout << "Enter square (topLeft_x topLeft_y side): ";
    readSquare(s);
    
    cout << "Point inside circle: " << (isPointInsideCircle(p, c) ? "Yes" : "No") << endl;
    cout << "Point on circle: " << (isPointOnCircle(p, c) ? "Yes" : "No") << endl;
    cout << "Point inside square: " << (isPointInsideSquare(p, s) ? "Yes" : "No") << endl;
    cout << "Point on square: " << (isPointOnSquare(p, s) ? "Yes" : "No") << endl << endl;
}

void demonstrateIntersections() {
    cout << "=== Intersections Demonstration ===" << endl;
    Circle c1, c2;
    Square s1, s2;
    
    cout << "Enter first circle (center_x center_y radius): ";
    readCircle(c1);
    cout << "Enter second circle (center_x center_y radius): ";
    readCircle(c2);
    cout << "Enter first square (topLeft_x topLeft_y side): ";
    readSquare(s1);
    cout << "Enter second square (topLeft_x topLeft_y side): ";
    readSquare(s2);
    
    cout << "Circles intersect: " << (circlesIntersect(c1, c2) ? "Yes" : "No") << endl;
    cout << "Squares intersect: " << (squaresIntersect(s1, s2) ? "Yes" : "No") << endl;
    cout << "Circle1 and Square1 intersect: " << (circleSquareIntersect(c1, s1) ? "Yes" : "No") << endl << endl;
}

void demonstrateContainment() {
    cout << "=== Containment Demonstration ===" << endl;
    Circle c1, c2;
    Square s1, s2;
    
    cout << "Enter first circle (center_x center_y radius): ";
    readCircle(c1);
    cout << "Enter second circle (center_x center_y radius): ";
    readCircle(c2);
    cout << "Enter first square (topLeft_x topLeft_y side): ";
    readSquare(s1);
    cout << "Enter second square (topLeft_x topLeft_y side): ";
    readSquare(s2);
    
    cout << "Circle1 inside Circle2: " << (isCircleInsideCircle(c1, c2) ? "Yes" : "No") << endl;
    cout << "Square1 inside Square2: " << (isSquareInsideSquare(s1, s2) ? "Yes" : "No") << endl;
    cout << "Square1 inside Circle1: " << (isSquareInsideCircle(s1, c1) ? "Yes" : "No") << endl;
    cout << "Circle1 inside Square1: " << (isCircleInsideSquare(c1, s1) ? "Yes" : "No") << endl;
}

int main() {
    demonstratePoint();
    demonstrateCircle();
    demonstrateSquare();
    demonstratePointInFigures();
    demonstrateIntersections();
    demonstrateContainment();
    
    return 0;
}