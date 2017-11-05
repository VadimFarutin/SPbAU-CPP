#include "circle.h"
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char* label)
	: Figure(id, x, y) {
	this->radius = radius;
	this->label = new char[strlen(label) + 1];
	strcpy(this->label, label);
}

Circle::~Circle() {
	delete []label;
}

void Circle::print() const {
	printf("Circle %i: x = %i y = %i radius = %i label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int x, int y) const {
	return (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= radius * radius;
}

void Circle::zoom(int factor) {
	radius *= factor;
}
