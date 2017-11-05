#include <cassert>
#include <cstddef>
#include <cstring>
#include <stdint.h>


template<typename T, std::size_t N>
class my_array {
private:
	T array_[N];

public:
	T& at(std::size_t index) {
		assert(index < N);
		return array_[index];
	}

	const T& at(std::size_t index) const {
		assert(index < N);
		return array_[index];
	}

	T& operator[](std::size_t index) {
		return array_[index];
	}

	const T& operator[](std::size_t index) const {
		return array_[index];
	}

	bool empty() const {
		return N == 0;
	}

	std::size_t size() const {
		return N;
	}

	void fill(const T& val) {
		for (std::size_t i = 0; i < N; i++)
			array_[i] = val;
	}
};

class proxy {
private:
	uint8_t *c_;
	std::size_t index_;

	proxy(uint8_t *c, std::size_t index) : c_(c), index_(index) {}

	template<typename T, std::size_t N>
	friend class my_array;

public:
	proxy& operator=(bool b) {
		if (b)
			*c_ |= (1 << (7 - index_));
		else
			*c_ &= ~(1 << (7 - index_));

		return *this;
	}

	operator bool() const {
		return (*c_ >> (7 - index_)) & 1;
	}
};

template<std::size_t N>
class my_array<bool, N> {
private:
	uint8_t array_[(N - 1) / 8 + 1];

public:
	my_array() {
		memset(array_, 0, (N - 1) / 8 + 1);
	}

	proxy at(std::size_t index) {
		assert(index < N);
		return proxy(&array_[index / 8], index % 8);
	}

	const proxy at(std::size_t index) const {
		assert(index < N);
		return proxy((uint8_t *)&array_[index / 8], index % 8);
	}

	proxy operator[](std::size_t index) {
		return proxy(&array_[index / 8], index % 8);
	}

	const proxy operator[](std::size_t index) const {
		return proxy((uint8_t *)&array_[index / 8], index % 8);
	}

	bool empty() const {
		return N == 0;
	}

	std::size_t size() const {
		return N;
	}

	void fill(const bool& val) {
		for (std::size_t i = 0; i < N; i++)
			(*this)[i] = val;
	}
};
