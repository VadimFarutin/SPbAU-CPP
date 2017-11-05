#include "matrix.h"
#include <iostream>

const int REGS_CNT = 10;

int read_reg() {
	char c;
	int index;

	std::cin >> c >> index;

	return index;
}

int main() {
	Matrix regs[REGS_CNT];
	std::string command;
	int reg1_index, reg2_index;

	while (true) {
		try {
			std::cin >> command;

			if (command == "exit") {
				break;
			}

			reg1_index = read_reg();

			if (command == "load") {
				std::string filename;
				std::cin >> filename;

				regs[reg1_index].load(filename);
			}
			else if (command == "print") {
				regs[reg1_index].print();
			}
			else if (command == "add") {
				reg2_index = read_reg();

				regs[reg1_index] += regs[reg2_index];
			}
			else if (command == "mul") {
				reg2_index = read_reg();

				regs[reg1_index] *= regs[reg2_index];
			}
			else if (command == "elem") {
				int i, j;
				std::cin >> i >> j;

				std::cout << regs[reg1_index].get(i, j) << '\n';
			}
		}
		catch (MatrixExeption& e) {
			std::cout << e.what() << '\n';
		}
	}

	return 0;
}