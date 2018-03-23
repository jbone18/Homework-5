#pragma once
#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>
using namespace std;

class Customer 
{
protected:
	string name;
	int age;
	string telephone;
	string address;
	string cust_type;
	int id;

public:
	Customer(string name_, int id_, string cust_type_)
	{
		name = name_;
		id = id_;
		cust_type = cust_type_;
	}

	int get_id() { return id; }
	int get_age() { return age; }
	string get_name() { return name; }
	string get_cust_type() { return cust_type; }
	string get_telephone() { return telephone; }
	string get_address() { return address; }


	void set_name(string name_cust)
	{
		name = name_cust;
	}
	void set_age(int age_cust)
	{
		age = age_cust;
	}
	void set_telephone(string telephone_cust)
	{
		telephone = telephone_cust;
	}
	void set_address(string address_cust)
	{
		address = address_cust;
	}
	void set_cust_type(string cust_type_)
	{
		cust_type = cust_type_;
	}
	void set_cust_id(int iD)
	{
		id = iD;
	}

	virtual const double get_overdraft_fees() = 0;
	virtual const double get_check_charge() = 0;
	virtual const double get_savings_interest() = 0;
	virtual const double get_checking_interest() = 0;
};

class Student : public Customer
{
public:
	Student(string name_, int id_, string cust_type_) : Customer(name_, id_, cust_type_) {};
	const double SAVINGS_INTEREST = 0.02;
	const double CHECK_INTEREST = 0.02;
	const double CHECK_CHARGE = 2.00;
	const double OVER_DRAFT = 25.00;

	const double get_overdraft_fees() { return OVER_DRAFT; }
	const double get_check_charge() { return CHECK_CHARGE; }
	const double get_savings_interest() { return SAVINGS_INTEREST; }
	const double get_checking_interest() { return CHECK_INTEREST; }
};

class Senior :public Customer
{
public:
	Senior(string name_, int id_, string cust_type_) : Customer(name_, id_, cust_type_) {};
	const double SAVINGS_INTEREST = 0.05;
	const double CHECK_INTEREST = 0.05;
	const double CHECK_CHARGE = 1.00;
	const double OVER_DRAFT = 35.00;

	const double get_overdraft_fees() { return OVER_DRAFT; }
	const double get_check_charge() { return CHECK_CHARGE; }
	const double get_savings_interest() { return SAVINGS_INTEREST; }
	const double get_checking_interest() { return CHECK_INTEREST; }
};

class Adult :public Customer
{
public:
	Adult(string name_, int id_, string cust_type_) : Customer(name_, id_, cust_type_) {};
	const double SAVINGS_INTEREST = 0.03;
	const double CHECK_INTEREST = 0.03;
	const double CHECK_CHARGE = 1.50;
	const double OVER_DRAFT = 30.00;

	const double get_overdraft_fees() { return OVER_DRAFT; }
	const double get_check_charge() { return CHECK_CHARGE; }
	const double get_savings_interest() { return SAVINGS_INTEREST; }
	const double get_checking_interest() { return CHECK_INTEREST; }
};

#endif