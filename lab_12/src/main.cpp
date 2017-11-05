#include <iostream>
#include <cstring>
#include <vector>
#include "my_vector.h"

class Product {
public:
	Product();
	Product(const char* name, int quantity, double price);
	Product(const Product& other);
	Product& operator=(Product other);
	~Product();
	bool operator==(const Product& other) const;

	friend std::ostream& operator<<(std::ostream& out, const Product& product);

private:
	char *name_;
	int quantity_;
	double price_;

	void swap(Product& other);
};

Product::Product() {
	name_ = new char[1];
	name_[0] = 0;

	quantity_ = 0;
	price_ = 0;
}

Product::Product(const char* name, int quantity, double price) {
	size_t size = strlen(name);
	name_ = new char[size + 1];
	strcpy(name_, name);

	quantity_ = quantity;
	price_ = price;
}

Product::Product(const Product& other) {
	size_t size = strlen(other.name_);
	name_ = new char[size + 1];
	strcpy(name_, other.name_);

	quantity_ = other.quantity_;
	price_ = other.price_;
}

Product& Product::operator=(Product other) {
	swap(other);
	return *this;
}

Product::~Product() {
	delete[]name_;
}

void Product::swap(Product& other) {
	std::swap(name_, other.name_);
	std::swap(quantity_, other.quantity_);
	std::swap(price_, other.price_);
}

bool Product::operator==(const Product& other) const {
	return strcmp(name_, other.name_) == 0 &&
		quantity_ == other.quantity_ &&
		price_ == other.price_;
}

std::ostream& operator<<(std::ostream& out, const Product& product) {
	out << product.name_ << " " << product.quantity_ << " " << product.price_;
	return out;
}

void print(const my_vector<Product>& v) {
	std::cout << v << std::endl;
}

int main() {
	test_my_vector<int>(5, 10);
	test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

	my_vector<int> vi;
	vi.push_back(5);
	vi.push_back(10);
	std::cout << vi << "\n";

	my_vector<Product> vp;
	vp.push_back(Product("asdf", 4, 12.0));
	vp.push_back(Product("qwe", -1, 7.5));
	print(vp);

	return 0;
}