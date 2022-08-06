#ifndef _CLIENT_OPERATIONS_HPP_
#define _CLIENT_OPERATIONS_HPP_

#include "Accounts/SavingsAccount.hpp"
#include "Accounts/CurrentAccount.hpp"
#include "FileOperations.hpp"

void depositAmount(long long account_number) {
	double amount;
	for (const auto &account : accounts) {
		if (account->getAccountNumber() == account_number) {
			std::cout << "Enter the amount to deposit: ";
			std::cin >> amount;

			if (account->deposit(amount)) {
				std::cout << "Rs. " << amount << " deposited successfully" << std::endl;
				writeInFile(accounts);
			} else
				std::cout << "Amount deposition unsuccessful" << std::endl;

			std::cout << "Balance in your account: Rs. " << account->getBalance() << std::endl;
			return;
		}
	}
	std::cout << "Invalid account number" << std::endl;
}

void withdrawAmount(long long account_number) {
	double amount;
	for (const auto &account : accounts) {
		if (account->getAccountNumber() == account_number) {
			std::cout << "Enter the amount to withdraw: ";
			std::cin >> amount;

			if (account->withdraw(amount)) {
				std::cout << "Rs. " << amount << " withdrawal successfully" << std::endl;
				writeInFile(accounts);
			} else
				std::cout << "Amount withdrawal unsuccessful" << std::endl;

			std::cout << "Balance in your account: Rs. " << account->getBalance() << std::endl;
			return;
		}
	}
	std::cout << "Invalid account number" << std::endl;
}

void displayBalance(long long account_number) {
	for (const auto &account : accounts) {
		if (account->getAccountNumber() == account_number) {
			std::cout << std::fixed << std::setprecision(2)
					  << "Balance in your account: Rs." << account->getBalance()
					  << std::endl;

			if (account->getAccountType() == 'C' && account->getOverdraftBalance() < CurrentAccount::getOverdraftLimit()) {
				std::cout << std::fixed << std::setprecision(2)
						  << "Overdraft funds used: Rs."
						  << CurrentAccount::getOverdraftLimit() - account->getOverdraftBalance()
						  << std::endl;
			}
			return;
		}
	}

	std::cout << "Invalid account number" << std::endl;
}

void refreshScreen() {
	char ch;
	std::cout << std::endl << std::endl;
	std::cout << "Press any key to continue and hit enter to continue" << std::endl;
	std::cin >> ch;

	system("cls");
}

#endif // _CLIENT_OPERATIONS_HPP_