#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <fstream>
#include <iostream>

class Employee {
protected:
	char *_name;
	int32_t _base_salary;

public:
	virtual ~Employee();

	virtual int salary() const = 0;
	virtual void read(std::istream &) = 0;
	virtual void fread(std::ifstream &) = 0;
	virtual void print(std::ostream &) const = 0;
	virtual void fprint(std::ofstream &) const = 0;

	friend std::istream & operator>>(std::istream &, Employee &);
	friend std::ifstream & operator>>(std::ifstream &, Employee &);
	friend std::ofstream & operator<<(std::ofstream &, const Employee &);
	friend std::ostream & operator<<(std::ostream &, const Employee &);
};

class Developer : public Employee {
public:
	int salary() const;
	void read(std::istream &);
	void fread(std::ifstream &);
	void print(std::ostream &) const;
	void fprint(std::ofstream &) const;

private:
  bool _has_bonus;
};

class SalesManager : public Employee {
public:
	int salary() const;
	void read(std::istream &);
	void fread(std::ifstream &);
	void print(std::ostream &) const;
	void fprint(std::ofstream &) const;

private:
	int32_t _sold_nm, _price;
};

class EmployeesArray {
private:
	Employee **_employees;
	int _sz;
	int _cp;

	friend std::ofstream & operator<<(std::ofstream &, const EmployeesArray &);
	friend std::ostream & operator<<(std::ostream &, const EmployeesArray &);

public:
	EmployeesArray();
	~EmployeesArray();

	void add(const Employee *e);
	int total_salary() const;
};

std::ifstream & operator>>(std::ifstream &fin, EmployeesArray &employees);

#endif
