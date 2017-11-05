#include <iostream>
#include <fstream>
#include <string>
#include "employees.h"

using namespace std;

int main() {
	EmployeesArray employees;
	char command[5];
	string filename;
	char *c_filename;

	while (true) {
		cin >> command;

		if (strcmp(command, "load") == 0) {
			cin >> filename;

			c_filename = new char[filename.size() + 1];
			strcpy(c_filename, filename.c_str());

			ifstream fin(c_filename, ios::binary);
			fin >> employees;

			delete c_filename;
		}
		else if (strcmp(command, "list") == 0) {
			cout << employees;
		}
		else if (strcmp(command, "add") == 0) {
			int type;
			cin >> type;

			if (type == 1) {
				Employee *developer = new Developer();
				cin >> *developer;
				employees.add(developer);
			}
			else if (type == 2) {
				Employee *salesManager = new SalesManager();
				cin >> *salesManager;
				employees.add(salesManager);
			}
		}
		else if (strcmp(command, "save") == 0) {
			cin >> filename;

			c_filename = new char[filename.size() + 1];
			strcpy(c_filename, filename.c_str());

			ofstream fout(filename, ios::binary);
			fout << employees;

			delete c_filename;
		}
		else {
			break;
		}
	}

	return 0;
}
