#ifndef _FILE_OPERATIONS_HPP_
#define _FILE_OPERATIONS_HPP_

#include "Accounts/SavingsAccount.hpp"
#include "Accounts/CurrentAccount.hpp"
#include <fstream>
#include <algorithm>

void readToProgram(std::vector<Account *> &acc) {
	acc.clear();

	std::ifstream savings_accounts;
	savings_accounts.open("./Database/SavingsAccounts.csv");
	if (!savings_accounts.is_open()) {
		std::cerr << "Cannot open savings account database" << std::endl;
		exit(1);
	}

	std::ifstream current_accounts;
	current_accounts.open("./Database/CurrentAccounts.csv");
	if (!current_accounts.is_open()) {
		std::cerr << "Cannot open current account database" << std::endl;
		exit(1);
	}

	long long AccountNumber;
	std::string name;
	double balance;
	size_t age;
	int rateOfInterest, i{0};
	double overdraft;

	std::vector<std::string> cells;
	std::string row, cell;

	while (getline(savings_accounts, row)) {
		cells.clear();

		std::stringstream ss(row);
		if (i == 0) {
			i++;
			continue;
		}

		while (getline(ss, cell, ','))
			cells.push_back(cell);

		AccountNumber = stoll(cells.at(0));
		name = cells.at(1);
		balance = stod(cells.at(2));
		age = stoul(cells.at(3));
		rateOfInterest = stoi(cells.at(4));

		Account *temp_account = new SavingsAccount(AccountNumber, name, balance, age, rateOfInterest);
		acc.push_back(temp_account);
	}

	i = 0;
	while (getline(current_accounts, row)) {
		cells.clear();
		std::stringstream ss(row);
		if (i == 0) {
			i++;
			continue;
		}

		while (getline(ss, cell, ','))
			cells.push_back(cell);

		AccountNumber = stoll(cells.at(0));
		name = cells.at(1);
		balance = stod(cells.at(2));
		overdraft = stod(cells.at(3));

		Account *temp_account = new CurrentAccount(AccountNumber, name, balance, overdraft);
		acc.push_back(temp_account);
	}

	//    std::sort(acc.begin(), acc.end(), [](Account *a, Account *b) {
	//    	return a->getAccountNumber() < b->getAccountNumber();
	//    });

	std::sort(acc.begin(), acc.end(), &sortComparator);
}

void writeInFile(const std::vector<Account *> &acc) {
	std::ofstream savings_accounts;
	savings_accounts.open("Database/SavingsAccounts.csv");
	if (!savings_accounts.is_open()) {
		std::cerr << "Cannot open savings account database" << std::endl;
		exit(1);
	}
	savings_accounts << "Account number" << ','
					 << "Name of account holder" << ','
					 << "Balance" << ','
					 << "Age of account holder" << ','
					 << "Rate of interest" << std::endl;

	std::ofstream current_accounts;
	current_accounts.open("Database/CurrentAccounts.csv");
	if (!current_accounts.is_open()) {
		std::cerr << "Cannot open current account database" << std::endl;
		exit(1);
	}
	current_accounts << "Account number" << ','
					 << "Name of account holder" << ','
					 << "Balance" << ','
					 << "Overdraft" << std::endl;

	for (const auto &a : acc) {
		if (a->getAccountType() == 'S')
			savings_accounts << a->writeData();
		else if (a->getAccountType() == 'C')
			current_accounts << a->writeData();
		else {
			std::cout << "Account type unknown of account number: " << a->getAccountNumber() << std::endl;
			exit(1);
		}
	}
}

#endif // _FILE_OPERATIONS_HPP_