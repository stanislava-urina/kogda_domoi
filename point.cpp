#include <iostream>

using namespace std;

struct Point {
	double x = 0;
	double y = 0;

	void setpoint(double X, double Y) {
		x = X;
		y = Y;
	}

	void pointPrint() {
		cout << "x: " << x << endl;
		cout << "y: " << y << endl;
	}
};

int main() {
	Point point;

	double x, y;
	cin >> x >> y;

	point.setpoint(x, y);
	point.pointPrint();

	return 0;
}
