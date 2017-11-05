#include "employees.h"
#include <string>

using namespace std;

Employee::~Employee() {
	if (_name != NULL)
		delete _name;
}

istream & operator>>(istream &fin, Employee &employee) {
	employee.read(fin);
	return fin;
}

ifstream & operator>>(ifstream &fin, Employee &employee) {
	employee.fread(fin);
	return fin;
}

ofstream & operator<<(ofstream &fout, const Employee &employee) {
	employee.fprint(fout);
	return fout;
}

ostream & operator<<(ostream &out, const Employee &employee) {
	employee.print(out);
	return out;
}

int Developer::salary() const {
	int salary = _base_salary;
	if (_has_bonus) { salary += 1000; }
	return salary;
}

void Developer::read(istream &fin) {
	string name;
	fin >> name;
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());

	fin >> _base_salary >> _has_bonus;
}

void Developer::fread(ifstream &fin) {
	string name;
	getline(fin, name, '\0');
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());

	fin.read((char *)&_base_salary, sizeof(_base_salary));
	fin.read((char *)&_has_bonus, sizeof(_has_bonus));
}

void Developer::fprint(ofstream &fout) const {
	int32_t type = 1;
	fout.write((char *)&type, sizeof(type));
	fout.write(_name, strlen(_name) + 1);
	fout.write((char *)&_base_salary, sizeof(_base_salary));
	fout.write((char *)&_has_bonus, sizeof(_has_bonus));
	
	//fout << 1 << _name << _base_salary << _has_bonus;
}

void Developer::print(ostream &out) const {
	out << "Developer\n";
	out << "Name: " << _name << "\n";
	out << "Base Salary: " << _base_salary << "\n";
	out << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
}

int SalesManager::salary() const {
	return _base_salary + _sold_nm * _price * 0.01;
}

void SalesManager::read(istream &fin) {
	string name;
	fin >> name;
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());

	fin >> _base_salary >> _sold_nm >> _price;
}

void SalesManager::fread(ifstream &fin) {
	string name;
	getline(fin, name, '\0');
	_name = new char[name.size() + 1];
	strcpy(_name, name.c_str());

	fin.read((char *)&_base_salary, sizeof(_base_salary));
	fin.read((char *)&_sold_nm, sizeof(_sold_nm));
	fin.read((char *)&_price, sizeof(_price));
}

void SalesManager::fprint(ofstream &fout) const {
	int32_t type = 2;
	fout.write((char *)&type, sizeof(type));
	fout.write(_name, strlen(_name) + 1);
	fout.write((char *)&_base_salary, sizeof(_base_salary));
	fout.write((char *)&_sold_nm, sizeof(_sold_nm));
	fout.write((char *)&_price, sizeof(_price));

	//fout << 2 << _name << _base_salary << _sold_nm << _price;
}

void SalesManager::print(ostream &out) const {
	out << "Sales Manager\n";
	out << "Name: " << _name << "\n";
	out << "Base Salary: " << _base_salary << "\n";
	out << "Sold items: " << _sold_nm << "\n";
	out << "Item price: " << _price << "\n";
}

EmployeesArray::EmployeesArray() {
	_sz = 0;
	_cp = 1;
	_employees = new Employee *[_cp];
}

EmployeesArray::~EmployeesArray() {
	for (int i = 0; i < _sz; i++)
		delete _employees[i];

	delete[]_employees;
}

void EmployeesArray::add(const Employee *e) {
	_sz++;

	if (_sz > _cp) {
		_cp *= 2;
		Employee **temp = new Employee *[_cp];
		for (int i = 0; i < _sz - 1; i++)
			temp[i] = _employees[i];

		std::swap(_employees, temp);
		delete[]temp;
	}

	_employees[_sz - 1] = (Employee *)e;
}

int EmployeesArray::total_salary() const {
	int salary = 0;
	for (int i = 0; i < _sz; i++)
		salary += _employees[i]->salary();

	return salary;
}

ifstream & operator>>(ifstream &fin, EmployeesArray &employees) {
	int32_t type;
	Developer *developer;
	SalesManager *salesManager;

	int32_t num;
	fin.read((char *)&num, sizeof(num));

	for (int i = 0; i < num; i++) {
		fin.read((char *)&type, sizeof(type));

		if (type == 1) {
			developer = new Developer();
			fin >> *developer;
			employees.add(developer);
		}
		else if (type == 2) {
			salesManager = new SalesManager();
			fin >> *salesManager;
			employees.add(salesManager);
		}
	}

	return fin;
}

ofstream & operator<<(ofstream &fout, const EmployeesArray &employees) {
	fout.write((char *)&employees._sz, sizeof(employees._sz));

	for (int i = 0; i < employees._sz; i++)
		fout << *(employees._employees[i]);

	return fout;
}

ostream & operator<<(ostream &out, const EmployeesArray &employees) {
	for (int i = 0; i < employees._sz; i++) {
		out << i + 1 << ". ";
		out << *(employees._employees[i]);
	}

	out << "== Total salary: " << employees.total_salary();

	return out;
}