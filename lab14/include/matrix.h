#pragma once

#include <cstddef>
#include <string>
#include <exception>

class Matrix {
public:
	Matrix();
	Matrix(std::size_t r, std::size_t c);
	Matrix(const Matrix& that);
	Matrix& operator=(Matrix that);
	~Matrix();

	int get(std::size_t i, std::size_t j) const;
	
	void load(const std::string& filename);
	void print() const;

	Matrix& operator+=(const Matrix& m);
	Matrix& operator*=(const Matrix& m);

private:
	std::size_t _rows;
	std::size_t _cols;
	int **_data;

	void swap(Matrix &m);
};

class MatrixExeption: public std::exception {
private:
	std::string _message;

public:
	MatrixExeption(const std::string& _m);
	~MatrixExeption() throw() {}
	const char* what() const throw();
};

