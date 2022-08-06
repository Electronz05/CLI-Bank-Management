#ifndef _MANAGER_OPERATIONS_HPP_
#define _MANAGER_OPERATIONS_HPP_

#include "Accounts/SavingsAccount.hpp"
#include "Accounts/CurrentAccount.hpp"
#include "FileOperations.hpp"
#include <limits>

bool openAccount(std::vector<Account *> &acc) {
	char account_type;
	long long account_number;
	std::string name;
	double opening_balance;

	std::cout << "Press 'S' for savings account and 'C' for current account" << std::endl
			  << "Enter the type of account you to open: ";
	std::cin >> account_type;

	switch (account_type) {
		case 'S':
		case 's': {
			size_t age;
			std::cout << "Enter the age of account holder: ";
			std::cin >> age;
			std::cout << std::endl;

			if (age < SavingsAccount::getMinimumAge()) {
				std::cout << "You are too young to open account" << std::endl
						  << "Try after " << SavingsAccount::getMinimumAge() - age << " years"
						  << std::endl;
				return false;
			}

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Enter full name of account holder: ";
			getline(std::cin, name);

			std::cout << "Enter the opening balance: ";
			std::cin >> opening_balance;
			if (opening_balance < SavingsAccount::getMinimumBalance()) {
				std::cerr << "Opening balance has to be more that Rs. "
						  << SavingsAccount::getMinimumBalance() << std::endl;
				return false;
			}

			if (Account::getNumberOfAccounts() == 0)
				account_number = 1;
			else
				account_number = accounts.back()->getAccountNumber() + 1;

			accounts.push_back(new SavingsAccount(account_number, name, opening_balance, age));
			std::cout << std::endl << std::endl << "Account number of this new account: " << account_number << std::endl;

			writeInFile(acc);
			return true;
		}

		case 'C':
		case 'c': {
			std::cout << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Enter the name of organization: ";
			getline(std::cin, name);

			std::cout << "Enter opening balance: ";
			std::cin >> opening_balance;
			if (opening_balance < CurrentAccount::getMinimumBalance()) {
				std::cerr << "Opening balance has to be more that Rs. "
						  << CurrentAccount::getMinimumBalance() << std::endl;
				return false;
			}

			if (Account::getNumberOfAccounts() == 0) {
				account_number = 1;
			} else {
				account_number = accounts.back()->getAccountNumber() + 1;
			}

			accounts.push_back(new CurrentAccount(account_number, name, opening_balance));
			std::cout << std::endl << std::endl << "Account number of this new account: " << account_number << std::endl;

			writeInFile(acc);
			return true;
		}

		default:
			std::cout << "Invalid Choice" << std::endl;
			return false;
	}
}

bool closeAccount(std::vector<Account *> &acc) {
	long long accountNumber;
	std::cout << "Enter the number: ";
	std::cin >> accountNumber;

	char choice;
	for (auto it = acc.begin(); it < acc.end(); it++) {
		if ((*it)->getAccountNumber() == accountNumber) {
			if ((*it)->getAccountType() == 'C' && (*it)->getOverdraftBalance() < CurrentAccount::getOverdraftLimit()) {
				std::cerr << "Deficit of overdraft funds in your current account" << std::endl;
				return false;
			}

			(*it)->display();

			std::cout << "Do you wish to delete account? [Y/N]: " << std::endl;
			std::cin >> choice;

			if (choice == 'Y' || choice == 'y') {
				if ((*it)->getAccountType() == 'C')
					CurrentAccount::deleteCurrentAccount();

				if ((*it)->getAccountType() == 'S')
					SavingsAccount::deleteSavingsAccount();

				accounts.erase(it);

				writeInFile(acc);
				return true;
			}
			return false;
		}
	}

	std::cout << "There is no account with account number: " << accountNumber << std::endl;
	return false;
}

void displayNumberOfAccounts() {
	std::cout << "There are a total of " << Account::getNumberOfAccounts()
			  << " accounts in the bank including "
			  << SavingsAccount::getNumberOfSavingsAccounts()
			  << " savings account and "
			  << CurrentAccount::getNumberOfCurrentAccounts()
			  << " current accounts" << std::endl;
}

void displayAllAccounts(const std::vector<Account *> &acc) {
	for (const auto &a : acc) {
		a->display();
		std::cout << std::endl;
	}
}

void refreshScreen() {
	char ch;
	std::cout << std::endl << std::endl;
	std::cout << "Press any key to continue and hit enter to continue" << std::endl;
	std::cin >> ch;

	system("cls");
}

#endif // _MANAGER_OPERATIONS_HPP_