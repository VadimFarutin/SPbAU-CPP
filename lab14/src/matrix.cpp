#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>

Matrix::Matrix()
	: _rows(0), _cols(0), _data(NULL) {}

Matrix::Matrix(std::size_t r, std::size_t c) {
	_rows = r;
	_cols = c;

	int *elemetns = new int[_rows * _cols]();
	_data = new int*[_rows];

	for (std::size_t i = 0; i < _rows; i++) {
		_data[i] = elemetns + _cols * i;

		for (std::size_t j = 0; j < _cols; j++)
			_data[i][j] = 0;
	}
}

Matrix::Matrix(const Matrix& that) {
	_rows = that._rows;
	_cols = that._cols;

	int *elemetns = new int[_rows * _cols]();
	_data = new int*[_rows];

	for (std::size_t i = 0; i < _rows; i++)
		_data[i] = elemetns + _cols * i;

	for (std::size_t i = 0; i < _rows; i++)
		for (std::size_t j = 0; j < _cols; j++)
			_data[i][j] = that._data[i][j];
}

Matrix& Matrix::operator=(Matrix that) {
	swap(that);
	return *this;
}

Matrix::~Matrix() {
	if (_rows != 0 && _cols != 0 && _data != NULL) {
		if (*_data != NULL)
			delete[] * _data;
		delete[] _data;
	}
}

int Matrix::get(std::size_t i, std::size_t j) const {
	if (i >= _rows || j >= _cols)
		throw MatrixExeption("ACCESS: bad index.");

	return _data[i][j];
}

void Matrix::load(const std::string& filename) {
	std::ifstream ifs(filename.c_str());

	ifs >> _rows >> _cols;
	Matrix temp(_rows, _cols);

	for (std::size_t i = 0; i < _rows; i++)
		for (std::size_t j = 0; j < _cols; j++)
			ifs >> temp._data[i][j];

	*this = temp;
}

void Matrix::print() const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++)
			std::cout << _data[i][j] << " ";

		std::cout << "\n";
	}
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (_cols != m._cols || _rows != m._rows)
		throw MatrixExeption("ADD: dimensions do not match.");

	for (std::size_t i = 0; i < _rows; i++)
		for (std::size_t j = 0; j < _cols; j++)
			_data[i][j] += m._data[i][j];

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	if (_cols != m._rows)
		throw MatrixExeption("MUL: #arg1.columns != #arg2.rows.");

	Matrix tmp(_rows, m._cols);

	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < m._cols; j++)
			for (std::size_t k = 0; k < _cols; k++)
				tmp._data[i][j] += _data[i][k] * m._data[k][j];
	}

	*this = tmp;
	return *this;
}

void Matrix::swap(Matrix &m) {
	std::swap(_rows, m._rows);
	std::swap(_cols, m._cols);
	std::swap(_data, m._data);
}

MatrixExeption::MatrixExeption(const std::string& m)
	: _message(m) {}

const char* MatrixExeption::what() const throw() {
	return _message.c_str();
}