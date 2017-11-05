#include "linq.h"
#include <math.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>

void example1() {
	int xs[] = { 1, 2, 3, 4, 5 };

	std::vector<int> res =
		from(xs, xs + 5)  // ����� �������� xs
		.select([](int x) { return x * x; })  // �������� � �������
		.where_neq(25)    // �������� ������ �������� != 25
		.where([](int x) { return x > 3; })   // �������� ������ �������� > 3
		.drop(2)          // ������ ��� �������� �� ������
		.to_vector();     // ������������� ��������� � ������

	std::vector<int> expected = { 16 };
	assert(res == expected);
}

void example2() {
	std::stringstream ss("1 2 3 -1 4");
	std::istream_iterator<int> in(ss), eof;

	std::vector<int> res =
		from(in, eof)  // ����� ����� �� �������� ������
		.take(4)       // �� ����� ������ �����
		.until_eq(-1)  // ��������� ������ ����� ��������� -1
		.to_vector();  // �������� ������ ��������� �����

	std::vector<int> expected = { 1, 2, 3 };
	assert(expected == res);

	int remaining;
	assert(ss >> remaining);
	assert(remaining == 4);
}

void example3() {
	int xs[] = { 1, 2, 3, 4, 5 };

	std::vector<double> res =
		from(xs, xs + 5)  // ����� �������� xs
		.select<double>([](int x) { return sqrt(x); })  // ������� ������
		.to_vector();     // ������������� ��������� � ������

	assert(res.size() == 5);
	for (std::size_t i = 0; i < res.size(); i++) {
		assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
	}
}

void example4() {
	std::stringstream iss("4 16");
	std::stringstream oss;
	std::istream_iterator<int> in(iss), eof;
	std::ostream_iterator<double> out(oss, "\n");

	from(in, eof)    // ����� ����� �� �������� ������
		.select([](int x) { return static_cast<int>(sqrt(x) + 1e-6); })  // ������� �� ������� ������
		.copy_to(out);  // ������� �� �����

	assert(oss.str() == "2\n4\n");
}

void example5() {
	std::vector<int> xs[] = { std::vector<int>(5, 1), std::vector<int>(5, 2), std::vector<int>(5, 3) };

	std::vector<std::vector<int>> res =
		from(xs, xs + 3)  // ����� �������� xs
		.where_neq(std::vector<int>(5, 2))    // �������� ������ �������� != 25
		.to_vector();     // ������������� ��������� � ������

	std::vector<std::vector<int>> expected = { std::vector<int>(5, 1), std::vector<int>(5, 3) };
	assert(res == expected);
}

int main() {
	example1();
	example2();
	example3();
	example4();
	example5();
	return 0;
}
