#ifndef _SAVINGS_ACCOUNT_HPP_
#define _SAVINGS_ACCOUNT_HPP_

#include "Account.hpp"

class SavingsAccount : public Account {
private:
	static constexpr size_t MINIMUM_AGE{18};
	static constexpr int DEFAULT_RATE_OF_INTEREST{4};
	static constexpr double MINIMUM_BALANCE{500.00};
	static constexpr double MAXIMUM_DEPOSIT_AMOUNT{40000.00};
	static constexpr double MAXIMUM_WITHDRAWAL_AMOUNT{25000.00};

protected:
	static size_t numberOfSavingsAccounts;
	size_t age;
	int rateOfInterest;

public:
	bool deposit(double) override;
	bool withdraw(double) override;
	void display() const override;

	static size_t getMinimumAge();
	static double getMinimumBalance();
	static void deleteSavingsAccount();
	static size_t getNumberOfSavingsAccounts();

	SavingsAccount &operator=(const SavingsAccount &);

	std::string writeData() const override;

	SavingsAccount(long long, std::string, double, size_t, int rateOfInterest = DEFAULT_RATE_OF_INTEREST);
	~SavingsAccount() override = default;
};

size_t SavingsAccount::numberOfSavingsAccounts{0};

SavingsAccount::SavingsAccount(long long accountNumber, std::string name, double balance, size_t age, int rateOfInterest)
: Account(accountNumber, std::move(name), balance), age{age}, rateOfInterest{rateOfInterest} {
	++numberOfSavingsAccounts;
	accountType = 'S';
}

bool SavingsAccount::deposit(double amount) {
	if (amount > MAXIMUM_DEPOSIT_AMOUNT) {
		std::cerr << "Amount available for deposit: " << MAXIMUM_DEPOSIT_AMOUNT << std::endl;
		return false;
	}

	amount += (amount * rateOfInterest / 100);
	return Account::deposit(amount);
}

bool SavingsAccount::withdraw(double amount) {
	if (amount > MAXIMUM_WITHDRAWAL_AMOUNT) {
		std::cerr << std::endl
				  << "Amount exceeds maximum withdrawal limit" << std::endl
				  << "Amount available for withdrawal: " << MAXIMUM_WITHDRAWAL_AMOUNT << std::endl;
		return false;
	} else if ((this->balance - amount) < MINIMUM_BALANCE) {
		char choice{};
		std::cerr << std::endl
				  << "Post withdrawal balance will be less than minimum balance" << std::endl;
		std::cout << "Do you wish to continue? [Y/N]: ";
		std::cin >> choice;

		if (choice == 'Y' || choice == 'y')
			return Account::withdraw(amount);
		return false;
	} else if (this->balance < MINIMUM_BALANCE) {
		std::cerr << std::endl
				  << "Account balance is less than minimum balance" << std::endl
				  << "Further withdrawal not possible" << std::endl;
		return false;
	} else if (amount > this->balance) {
		std::cerr << "Insufficient balance in your account" << std::endl;
		return false;
	} else {
		return Account::withdraw(amount);
	}
}

void SavingsAccount::display() const {
	Account::display();
	std::cout << "Age of account holder: " << this->age << std::endl
			  << "Rate of interest: " << this->rateOfInterest << std::endl;
}

size_t SavingsAccount::getMinimumAge() {
	return SavingsAccount::MINIMUM_AGE;
}

double SavingsAccount::getMinimumBalance() {
	return SavingsAccount::MINIMUM_BALANCE;
}

void SavingsAccount::deleteSavingsAccount() {
	Account::deleteAccount();
	--SavingsAccount::numberOfSavingsAccounts;
}

size_t SavingsAccount::getNumberOfSavingsAccounts() {
	return SavingsAccount::numberOfSavingsAccounts;
}

std::string SavingsAccount::writeData() const {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2)
	   << this->accountNumber << ','
	   << this->name << ','
	   << this->balance << ','
	   << this->age << ','
	   << this->rateOfInterest << std::endl;
	return ss.str();
}

SavingsAccount &SavingsAccount::operator=(const SavingsAccount &sav) {
	if (this != &sav) {
		Account::operator=(sav);
		this->rateOfInterest = sav.rateOfInterest;
		this->age = sav.age;
	}

	return *this;
}

#endif // _SAVINGS_ACCOUNT_HPP_