#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c) {
	_rows = r;
	_cols = c;
	int *elemetns = new int [_rows * _cols]();
	_data = new int* [_rows];
	for (std::size_t i = 0; i < _rows; i++) {
		_data[i] = elemetns + _cols * i;
		for (std::size_t j = 0; j < _cols; j++)
			_data[i][j] = 0;
	}
}

Matrix::Matrix(const Matrix& that) {
	_rows = that._rows;
	_cols = that._cols;
	int *elemetns = new int [_rows * _cols]();
	_data = new int* [_rows];
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
	delete [] *_data;
	delete [] _data;
}

std::size_t Matrix::get_rows() const {
	return _rows;
}

std::size_t Matrix::get_cols() const {
	return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
	_data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
	return _data[i][j];
}

void Matrix::print(FILE* f) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++)
			fprintf(f, "%i ", _data[i][j]);
		fprintf(f, "\n");
	}
}

bool Matrix::operator==(const Matrix& m) const{
	if (_rows != m._rows || _cols != m._cols)
		return false;
	for (std::size_t i = 0; i < _rows; i++)
		for (std::size_t j = 0; j < _cols; j++)
			if (_data[i][j] != m._data[i][j])
				return false;
	return true;
}

bool Matrix::operator!=(const Matrix& m) const{
	return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
	for (std::size_t i = 0; i < _rows; i++)
		for (std::size_t j = 0; j < _cols; j++)
			_data[i][j] += m._data[i][j];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	for (std::size_t i = 0; i < _rows; i++)
		for (std::size_t j = 0; j < _cols; j++)
			_data[i][j] -= m._data[i][j];
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	Matrix tmp(_rows, m._cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < m._cols; j++)
			for (std::size_t k = 0; k < _cols; k++)
				tmp._data[i][j] += _data[i][k] * m._data[k][j];
	}
	*this = tmp;
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
	Matrix tmp(*this);
	return tmp += m;
}

Matrix Matrix::operator-(const Matrix& m) const {
	Matrix tmp(*this);
	return tmp -= m;
}

Matrix Matrix::operator*(const Matrix& m) const {
	Matrix tmp(*this);
	return tmp *= m;
}

void Matrix::swap(Matrix &m) {
	std::swap(_rows, m._rows);
	std::swap(_cols, m._cols);
	std::swap(_data, m._data);
}
