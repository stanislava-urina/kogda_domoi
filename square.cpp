#include <iostream>

using namespace std;

struct Square {
	double x, y;
	int len;

	void setSquare(double X, double Y, int Len) {
		x = X;
		y = Y;
		len = Len;
	}

	void printSquare() {
		cout << "x левого верхнего угла: " << x << endl;
		cout << "y левого верхнего угла: " << y << endl;
		cout << "длина стороны: " << len << endl;
	}

	void SumSquare() {
		cout << "Периметр квадрата: " << len * 4 << endl;
	}

	void SquareSquare() {
		cout << "Площадь квадрата: " << len * len << endl;
	}
};

int main() {
	Square square;

	double x, y;
	int len;

	cin >> x >> y >> len;

	square.setSquare(x, y, len);
	square.printSquare();
	square.SumSquare();
	square.SquareSquare();

	return 0;
}