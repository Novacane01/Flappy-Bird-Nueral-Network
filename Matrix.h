#pragma once
#include <vector>

class Matrix {
public:
	Matrix(int, int);
	Matrix add(Matrix);
	Matrix add(double);
	Matrix subtract(Matrix);
	Matrix multiply(Matrix);
	Matrix sigmoid();
	void randomize();
	void print();
	std::vector<std::vector<double>> matrix;
private:
	int rows, columns;
};