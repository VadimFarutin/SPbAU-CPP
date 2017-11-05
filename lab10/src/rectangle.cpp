#include "rectangle.h"
#include <algorithm>

Rectangle::Rectangle(int id, int x, int y, int width, int height)
	: Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const {
	printf("Rectangle %i: x = %i y = %i width = %i height = %i\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int x, int y) const {
	return abs(this->x - x) * 2 <= width && abs(this->y - y) * 2 <= height;
}

void Rectangle::zoom(int factor) {
	width *= factor;
	height *= factor;
}
