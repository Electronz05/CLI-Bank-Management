#ifndef _CURRENT_ACCOUNT_HPP_
#define _CURRENT_ACCOUNT_HPP_

#include "Account.hpp"

class CurrentAccount : public Account {
private:
	static constexpr double CHARGE_PER_WITHDRAWAL{50.00};
	static constexpr double MINIMUM_BALANCE{10000.00};
	static constexpr double OVERDRAFT_LIMIT{500000.00};
	static constexpr double MINIMUM_BALANCE_FORFEIT{500.00};
	static constexpr double OVERDRAFT_USAGE_INTEREST{13.5};

protected:
	static size_t numberOfCurrentAccounts;
	double overdraft;

public:
	bool deposit(double) override;
	bool withdraw(double) override;
	void display() const override;

	double getOverdraftBalance() const override;

	static double getOverdraftLimit();
	static double getMinimumBalance();
	static void deleteCurrentAccount();
	static size_t getNumberOfCurrentAccounts();

	CurrentAccount &operator=(const CurrentAccount &);

	std::string writeData() const override;

	CurrentAccount(long long, std::string, double, double overdraft = OVERDRAFT_LIMIT);
	~CurrentAccount() override = default;
};

size_t CurrentAccount::numberOfCurrentAccounts{0};

CurrentAccount::CurrentAccount(long long accountNumber, std::string name, double balance, double overdraft)
: Account(accountNumber, std::move(name), balance), overdraft{overdraft} {
	++numberOfCurrentAccounts;
	accountType = 'C';
}

bool CurrentAccount::deposit(double amount) {
	if (this->overdraft < OVERDRAFT_LIMIT) {
		double overdraftUsageCharges = (CurrentAccount::OVERDRAFT_LIMIT - this->overdraft) * OVERDRAFT_USAGE_INTEREST / 100;

		if ((this->balance + amount - overdraftUsageCharges) > MINIMUM_BALANCE) {
			this->balance = amount - OVERDRAFT_LIMIT + overdraft - overdraftUsageCharges;
			overdraft = OVERDRAFT_LIMIT;
			return true;
		} else {
			std::cout << "Overdraft facility in this account is in use" << std::endl
					  << "You need a to depositAmount a minimum sum of Rs."
					  << OVERDRAFT_LIMIT + overdraftUsageCharges + MINIMUM_BALANCE - overdraft
					  << " to bring account balance to minimum balance" << std::endl;
			return false;
		}
	} else if (this->balance < MINIMUM_BALANCE) {
		if ((this->balance + amount - MINIMUM_BALANCE_FORFEIT) > MINIMUM_BALANCE) {
			amount -= MINIMUM_BALANCE_FORFEIT;
			return Account::deposit(amount);
		} else {
			std::cout << "Account balance is less that minimum balance" << std::endl
					  << "You need a to depositAmount a minimum sum of Rs."
					  << MINIMUM_BALANCE - this->balance + MINIMUM_BALANCE_FORFEIT
					  << " to bring account balance to minimum balance" << std::endl;
			return false;
		}
	} else {
		return Account::deposit(amount);
	}
}

bool CurrentAccount::withdraw(double amount) {
	if (this->balance == 0 && this->overdraft < OVERDRAFT_LIMIT) {
		std::cerr << "Overdraft funds are already in use" << std::endl
				  << "Further withdrawal suspended" << std::endl;
		return false;
	} else if (amount > this->balance) {
		char choice;
		std::cerr << "Insufficient balance in your account" << std::endl << std::endl
				  << "You have Rs. " << this->overdraft
				  << " in your overdraft balance which can be used at an interest of "
				  << OVERDRAFT_USAGE_INTEREST << "%" << std::endl
				  << "The amount will be deducted in next depositAmount" << std::endl << std::endl
				  << "Enter 'Y' to continue and 'N' to cancel" << std::endl
				  << "Would you like to use overdraft facility [Y/N]: ";
		std::cin >> choice;

		if (choice == 'Y' || choice == 'y') {
			overdraft -= (amount - this->balance);
			this->balance = 0;
			return true;
		}
		return false;
	} else if ((this->balance - amount) < MINIMUM_BALANCE) {
		char choice;
		std::cerr << "Post withdrawal balance will be less than Minimum Account Balance" << std::endl
				  << "You will be charged Rs." << MINIMUM_BALANCE_FORFEIT << std::endl;
		std::cout << "Do you wish to continue? [Y/N]: ";
		std::cin >> choice;

		if (choice == 'Y' || choice == 'y') {
			amount += CHARGE_PER_WITHDRAWAL;
			return Account::withdraw(amount);
		}
		return false;
	} else if (amount < 0) {
		std::cerr << "Amount cannot be less than zero" << std::endl;
		return false;
	} else {
		amount += CHARGE_PER_WITHDRAWAL;
		return Account::withdraw(amount);
	}
}

void CurrentAccount::display() const {
	Account::display();
	if (overdraft < OVERDRAFT_LIMIT)
		std::cout << "Overdraft used: " << CurrentAccount::OVERDRAFT_LIMIT - this->getOverdraftBalance() << std::endl;
}

double CurrentAccount::getOverdraftBalance() const {
	return this->overdraft;
}

double CurrentAccount::getOverdraftLimit() {
	return CurrentAccount::OVERDRAFT_LIMIT;
}

double CurrentAccount::getMinimumBalance() {
	return CurrentAccount::MINIMUM_BALANCE;
}

void CurrentAccount::deleteCurrentAccount() {
	Account::deleteAccount();
	--CurrentAccount::numberOfCurrentAccounts;
}

size_t CurrentAccount::getNumberOfCurrentAccounts() {
	return CurrentAccount::numberOfCurrentAccounts;
}

std::string CurrentAccount::writeData() const {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2)
	   << this->accountNumber << ','
	   << this->name << ','
	   << this->balance << ','
	   << this->overdraft << std::endl;
	return ss.str();
}

CurrentAccount &CurrentAccount::operator=(const CurrentAccount &curr) {
	if (this != &curr) {
		Account::operator=(curr);
		this->overdraft = curr.overdraft;
	}
	return *this;
}

#endif // _CURRENT_ACCOUNT_HPP_