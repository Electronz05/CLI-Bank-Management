#ifndef _ACCOUNT_HPP_
#define _ACCOUNT_HPP_

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <utility>

class Account {
	friend bool sortComparator(const Account *, const Account *);

protected:
	static size_t numberOfAccounts;
	long long accountNumber;
	std::string name;
	double balance;
	char accountType;

public:
	virtual bool deposit(double);
	virtual bool withdraw(double);
	virtual void display() const;

	long long getAccountNumber() const;
	double getBalance() const;
	char getAccountType() const;
	static void deleteAccount();
	static size_t getNumberOfAccounts();

	Account &operator=(const Account &);

	virtual std::string writeData() const;

	virtual double getOverdraftBalance() const;

	Account(long long accountNumber, std::string name, double balance);
	virtual ~Account() = default;
};

size_t Account::numberOfAccounts{0};

Account::Account(long long accountNumber, std::string name, double balance)
: accountNumber{accountNumber}, name{std::move(name)}, balance{balance} {
	++numberOfAccounts;
	accountType = '\0';
}

bool Account::deposit(double amount) {
	if (amount < 0)
		return false;

	this->balance += amount;
	return true;
}

bool Account::withdraw(double amount) {
	if (amount < 0)
		return false;

	this->balance -= amount;
	return true;
}

void Account::display() const {
	std::cout << std::fixed << std::setprecision(2)
			  << "Account number: " << this->accountNumber << std::endl
			  << "Name of account holder: " << this->name << std::endl
			  << "Type of account: " << this->accountType << std::endl
			  << "Balance in this account: " << this->balance << std::endl;
}

long long Account::getAccountNumber() const {
	return this->accountNumber;
}

double Account::getBalance() const {
	return this->balance;
}

char Account::getAccountType() const {
	return this->accountType;
}

void Account::deleteAccount() {
	--Account::numberOfAccounts;
}

size_t Account::getNumberOfAccounts() {
	return Account::numberOfAccounts;
}

bool sortComparator(const Account *acc1, const Account *acc2) {
	return acc1->accountNumber < acc2->accountNumber;
}

std::string Account::writeData() const {
	std::stringstream ss;
	ss << this->accountNumber << ','
	   << this->name << ','
	   << this->balance << std::endl;
	return ss.str();
}

Account &Account::operator=(const Account &acc) {
	if (this != &acc) {
		this->accountNumber = acc.accountNumber;
		this->name = acc.name;
		this->balance = acc.balance;
	}
	return *this;
}

double Account::getOverdraftBalance() const {
	return 0;
}

std::vector<Account *> accounts;

#endif // _ACCOUNT_HPP_