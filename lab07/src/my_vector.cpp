#include "../include/my_vector.h"

MyVector::MyVector() {
	_cp = 2;
	_sz = 0;
	_data = new int[_cp];
}
MyVector::MyVector(std::size_t init_capacity) {
	_cp = init_capacity;
	_sz = 0;
	_data = new int[_cp];
}
MyVector::~MyVector() {
	delete []_data;
}

void MyVector::set(std::size_t index, int value) {
	_data[index] = value;
}
int MyVector::get(std::size_t index) {
	return _data[index];
}

std::size_t MyVector::size() {
	return _sz;
}
std::size_t MyVector::capacity() {
	return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
	if (new_capacity > _cp) {
		int *old_data = _data;
		_cp = new_capacity;
		_data = new int[_cp];
		for (int i = 0; i < _sz; i++)
			_data[i] = old_data[i];
		delete[]old_data;
	}	
}
void MyVector::resize(std::size_t new_size) {
	if (new_size > _cp)
		reserve(new_size);
	for (int i = _sz; i < new_size; i++)
		_data[i] = 0;
	_sz = new_size;
}

void MyVector::push_back(int value) {
	if (_sz == _cp)
		reserve(_cp * 2);
	_data[_sz++] = value;
}
void MyVector::insert(std::size_t index, int value) {
	if (_sz == _cp)
		reserve(_cp * 2);
	for (int i = _sz; i > index; i--)
		_data[i] = _data[i - 1];
	_data[index] = value;
	_sz++;
}
void MyVector::erase(std::size_t index) {
	for (int i = index; i < _sz - 1; i++)
		_data[i] = _data[i + 1];
	_sz--;
}
