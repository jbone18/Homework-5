#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <vector>
#include <sstream>
#include "Customer.h"
#include "Transaction.h"
#include "Bank.h"
using namespace std;

class Savings_Account;
class Checking_Account;

class Account 
{
protected:
	// The customer who owns this account
	Customer * customer;		
	// The available balance in this account
	double balance;			
	// A unique number identifying this account
	int account_number;		
	// The record of transactions that have occured with this account
	vector<Transaction *> transactions;  
    /*Describe fees associated with the customer who owns this account.
	   The fee will depend on the specific type of customer.
	   @return string showing checking and overdraft fees*/
	string get_fees()
	{
		int overdraft;
		int charge;

		charge = customer->get_check_charge();
		overdraft = customer->get_overdraft_fees();

		stringstream ss;
		ss << "Check Charge: " << charge << " Overdraft Fee: " << overdraft;
		return ss.str();
	}
protected:
	/*Add interest based on a specified interest rate to account
	  @param interest	The interest rate*/
	void add_interest(double interest) 
	{
		double amt = balance * interest;
		balance = balance + amt;
		string fees = get_fees();
		Transaction *tran = NULL;

		int cust_id = customer->get_id();
		string type = "Add interest";

		tran = new Transaction(cust_id, type, amt, fees);

		transactions.push_back(tran);
	}
public:
	/*Constructor requires a customer to create an account
	  Balance always starts with 0 when account is created.*/
	Account(Customer *cust, int id) : customer(cust), account_number(id), balance(0) {}
	//Generic accesser and setter methods for properties customer, balance, and account_number
	Customer *get_customer() 
	{
		return customer;
	}
	void set_customer(Customer *cust) 
	{
		customer = cust;
	}
	int get_account() 
	{
		return account_number;
	}
	void set_balance(double new_balance) 
	{
		balance = new_balance;
	}
	void set_account(int account_number) 
	{
		this->account_number = account_number;
	}
	double get_balance() 
	{
		return balance;
	}
	/*Generic method describing the account information.
	  Remember that you will need to indicate if an account is Savings or Checking in
	  an overridden version of to_string() in the derived classes.
	  @return string describing generic information about the account*/
	virtual string to_string();
	//Deposits amount into account
	virtual void deposit(double amt) 
	{
		balance += amt;
		string fees = get_fees();
		Transaction *tran = NULL;

		int cust_id = customer->get_id();
		string type = "Deposit";

		tran = new Transaction(cust_id, type, amt, fees);

		transactions.push_back(tran);
	}
	//Withdraws amount from account
	virtual void withdraw(double amt) 
	{
		balance -= amt;
		std::string fees = get_fees();
		Transaction *tran = NULL;

		int cust_id = customer->get_id();
		string type = "withdrawal";

		tran = new Transaction(cust_id, type, amt, fees);

		transactions.push_back(tran);
	}
	// We want the Savings_Account and Checking_Account to implement this.
	virtual void add_interest() = 0;
};

class Savings_Account : public Account
{
public:
	//Constructor that takes the cust (name, account type) and the account number (id)
	Savings_Account(Customer *cust, int id) : Account(cust, id) {}

	void deposit(double amt) { balance += amt; }
	void withdrawal(double amt) { balance -= amt; }
	void add_interest()
	{
		double sav_interest = customer->get_savings_interest();
		double interest = balance * sav_interest;
		balance += interest;
	}
	string tostring()
	{
		stringstream ss;

		ss << "  Savings Account" << endl;

		return ss.str();
	}
	friend class Account;
};

class Checking_Account : public Account
{
protected:
public:
	Checking_Account(Customer *cust, int id) : Account(cust, id) {}
	void deposite(double amt) { balance += amt; }
	void withdrawal(double amt) { balance -= amt; }
	void add_interest()
	{
		double check_interest = customer->get_checking_interest();
		double interest = balance * check_interest;
		balance += interest;
	}
	string tostring()
	{
		stringstream ss;

		ss << "  Checking Account" << endl;

		return ss.str();
	}
	friend class Account;
};

/*Generic method describing the account information.
Remember that you will need to indicate if an account is Savings or Checking in
an overridden version of to_string() in the derived classes.
@return string describing generic information about the account*/
string Account::to_string()
{
	stringstream ss; // for composing the string that describes this account

					 // FIXME: Add information about the customer who owns this account.
	ss << "  Name: " << customer->get_name() << endl;
	ss << "  Age: " << customer->get_age() << endl;
	ss << "  Customer ID: " << customer->get_id() << endl;
	ss << "  Telephone: " << customer->get_telephone() << endl;
	ss << "  Address: " << customer->get_address() << endl;
	ss << "  Customer type: " << customer->get_cust_type() << endl;
	ss << "  Check Charge: " << customer->get_check_charge() << endl;
	ss << "  Overdraft Fees: " << customer->get_overdraft_fees() << endl;

	if (typeid(Savings_Account) == typeid(*this))
	{
		ss << dynamic_cast<Savings_Account*>(this)->tostring();
	}
	else if (typeid(Checking_Account) == typeid(*this))
	{
		ss << dynamic_cast<Checking_Account*>(this)->tostring();
	}


	ss << "  Balance: " << balance << endl;
	ss << "  Account ID: " << account_number << endl;
	return ss.str();
}
#endif