#include "stdafx.h"
#include "Matrix.h"
#include <cstring>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

Matrix::Matrix(int row, int column):matrix(row,std::vector<double>(column)) {
	this->rows = row;
	this->columns = column;
}

Matrix Matrix::add(Matrix m) {
	assert(rows == m.rows&&columns == m.columns);
	Matrix newMatrix(rows,columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			newMatrix.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
		}
	}
	return newMatrix;
}

Matrix Matrix::add(double n) {
	Matrix newMatrix(rows, columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			newMatrix.matrix[i][j] = matrix[i][j] + n;
		}
	}
	return newMatrix;
}


Matrix Matrix::subtract(Matrix m) {
	assert(rows == m.rows&&columns == m.columns);
	Matrix newMatrix(rows, columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			newMatrix.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
		}
	}
	return newMatrix;
}

Matrix Matrix::multiply(Matrix m) {
	assert(columns == m.rows);
	Matrix newMatrix(rows,m.columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			for (int k = 0; k < m.columns;k++) {
				newMatrix.matrix[i][k] += matrix[i][j] * m.matrix[j][k];
			}
		}
	}
	return newMatrix;
}

void Matrix::randomize() {
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			matrix[i][j] = ((float)rand()/RAND_MAX)*2-1;
		}
	}
}

void Matrix::print() {
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			std::cout << matrix[i][j] << " " << std::endl;
		}
		std::cout << std::endl;
	}
}

Matrix Matrix::sigmoid() {
	Matrix newMatrix(rows,columns);
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			newMatrix.matrix[i][j] = 1 / (1 + exp(-matrix[i][j]));
		}
	}
	return newMatrix;
}