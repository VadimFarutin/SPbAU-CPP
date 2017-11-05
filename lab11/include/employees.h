#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <fstream>
#include <iostream>

class Employee {
protected:
	char *_name;
	int32_t _base_salary;

private:
	Employee & operator=(const Employee &);
	Employee(const Employee &);

	virtual void read(std::istream &) = 0;
	virtual void fread(std::ifstream &) = 0;
	virtual void print(std::ostream &) const = 0;
	virtual void fprint(std::ofstream &) const = 0;

public:
	Employee() {};
	virtual ~Employee();

	virtual int salary() const = 0;
	
	friend std::istream & operator>>(std::istream &, Employee &);
	friend std::ifstream & operator>>(std::ifstream &, Employee &);
	friend std::ofstream & operator<<(std::ofstream &, const Employee &);
	friend std::ostream & operator<<(std::ostream &, const Employee &);
};

class Developer : public Employee {
private:
  	bool _has_bonus;

	void read(std::istream &);
	void fread(std::ifstream &);
	void print(std::ostream &) const;
	void fprint(std::ofstream &) const;


public:
	int salary() const;
};

class SalesManager : public Employee {
private:
	int32_t _sold_nm, _price;

	void read(std::istream &);
	void fread(std::ifstream &);
	void print(std::ostream &) const;
	void fprint(std::ofstream &) const;

public:
	int salary() const;
};

class EmployeesArray {
private:
	Employee **_employees;
	int _sz;
	int _cp;

	EmployeesArray(const EmployeesArray &);
	EmployeesArray & operator=(const EmployeesArray &);	

public:
	EmployeesArray();
	~EmployeesArray();

	void add(const Employee *e);
	int total_salary() const;

	friend std::ofstream & operator<<(std::ofstream &, const EmployeesArray &);
	friend std::ostream & operator<<(std::ostream &, const EmployeesArray &);
};

std::ifstream & operator>>(std::ifstream &fin, EmployeesArray &employees);

#endif
