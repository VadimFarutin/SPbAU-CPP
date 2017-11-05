#pragma once

#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cassert>

template <class T>
class my_vector {
public:
	my_vector(size_t n = 0) {
		size_ = n;
		capacity_ = getCapacity(n);
		
		array_ = (T*)new char[capacity_ * sizeof(T)];
		for (size_t i = 0; i < size_; i++)
			new (array_ + i) T();
	}

	my_vector(const my_vector& other) {
		size_ = other.size_;
		capacity_ = other.capacity_;
		
		array_ = (T*)new char[capacity_ * sizeof(T)]; 
		for (size_t i = 0; i < size_; i++)
			new (array_ + i) T(other[i]);
	}

	my_vector& operator=(my_vector other) {
		swap(other);
		return *this;
	}

	~my_vector() {
		for (size_t i = 0; i < size_; i++)
			array_[i].~T();
		
		delete[](char *)array_;
	}

	size_t size() const {
		return size_;
	}

	size_t capacity() const {
		return capacity_;
	}

	bool empty() const {
		return size_ == 0;
	}

	void resize(size_t n) {
		reserve(n);

		for (size_t i = size_; i < n; i++)
			new (array_ + i) T();

		size_ = n;
	}

	void reserve(size_t n) {
		if (n > capacity_) {
			capacity_ = getCapacity(n);

			T *temp = (T*)new char[capacity_ * sizeof(T)];
			for (size_t i = 0; i < size_; i++)
				new (temp + i) T(array_[i]);

			std::swap(array_, temp);

			for (size_t i = 0; i < size_; i++)
				temp[i].~T();

			delete[](char *)temp;
		}
	}

	T& operator[](size_t index) {
		return array_[index];
	}

	const T& operator[](size_t index) const {
		return array_[index];
	}

	void push_back(const T& t) {
		reserve(size_ + 1);
		new (array_ + size_) T(t);
		size_++;
	}

	void pop_back() {
		size_--;
		array_[size_].~T();
	}

	void clear() {
		for (size_t i = 0; i < size_; i++)
			array_[i].~T();
		
		delete[](char *)array_;

		size_ = 0;
		capacity_ = 1;
		array_ = (T*)new char[capacity_ * sizeof(T)];
	}

private:
	size_t capacity_;
	size_t size_;
	T* array_;

	size_t getCapacity(size_t n) const {
		size_t k = 1;
		
		while (k < n)
			k += k;

		return k;
	}

	void swap(my_vector& other) {
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
		std::swap(array_, other.array_);
	}
};

template <class T>
std::ostream& operator<<(std::ostream& out, const my_vector<T>& v) {
	for (size_t i = 0; i < v.size(); i++)
		out << v[i] << " ";

	return out;
}

template <class T>
void test_my_vector(T first, T second) {
	my_vector<T> vector;

	assert(vector.capacity() == 1);
	assert(vector.size() == 0);
	assert(vector.empty() == true);

	vector.reserve(5);
	assert(vector.capacity() == 8);

	vector.resize(3);
	assert(vector.size() == 3);

	vector.push_back(first);
	assert(vector.size() == 4);

	vector.push_back(second);
	assert(vector.size() == 5);
	
	vector.pop_back();
	assert(vector.size() == 4);

	vector[3] = second;
	assert(vector[3] == second);

	my_vector<T> vector2(vector);
	assert(vector2.capacity() == vector.capacity());
	assert(vector2.size() == vector.size());
	assert(vector2.empty() == false);

	vector2.clear();
	assert(vector2.capacity() == 1);
	assert(vector2.size() == 0);
	assert(vector2.empty() == true);

	my_vector<T> vector3(3);
	assert(vector3.capacity() == 4);
	assert(vector3.size() == 3);
	assert(vector3.empty() == false);

	vector3.push_back(first);
	assert(vector3.capacity() == 4);
	assert(vector3.size() == 4);

	vector3.push_back(second);
	assert(vector3.capacity() == 8);
	assert(vector3.size() == 5);

	vector3 = vector;
	assert(vector3.capacity() == vector.capacity());
	assert(vector3.size() == vector.size());
	assert(vector3.empty() == false);
}