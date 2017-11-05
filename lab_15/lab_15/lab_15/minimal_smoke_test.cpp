#include "linq.h"
#include <assert.h>
#include <vector>

void from_to_vector() {
	std::vector<int> xs = { 1, 2, 3 };
	std::vector<int> res = from(xs.begin(), xs.end()).to_vector();
	assert(res == xs);
}

void from_select() {
	const int xs[] = { 1, 2, 3 };
	std::vector<int> res = from(xs, xs + 3).select([](int x) { return x + 5; }).to_vector();
	std::vector<int> expected = { 6, 7, 8 };
	assert(res == expected);
}

void from_drop_select() {
	const int xs[] = { 1, 2, 3 };
	std::vector<int> res = from(xs, xs + 3).drop(1).select([](int x) { return x + 5; }).to_vector();
	std::vector<int> expected = { 7, 8 };
	assert(res == expected);
}

void from_until_drop_select() {
	const int xs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	std::vector<int> res =
		from(xs, xs + 9) // 1, 2, 3, 4, 5, 6, 7, 8, 9
		.until([](int x) { return x != 10; }) // 1, 2, 3, 4, 5, 6, 7, 8, 9
		.drop(1) // 2, 3, 4, 5, 6, 7, 8, 9
		.select([](int x) { return x + 5; }) // 7, 8, 9, 10, 11, 12, 13, 14
		.take(5) // 7, 8, 9, 10, 11
		.until_eq(11) // 7, 8, 9
		.where([](int x) { return x % 2 == 0; }) // 8
		.to_vector();
	std::vector<int> expected = { 8, 10 };
	assert(res == expected);
}
/*
int main() {
	from_to_vector();
	from_select();
	from_drop_select();
	from_until_drop_select();
	return 0;
}*/
