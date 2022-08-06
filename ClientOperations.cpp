#include "ClientOperations.hpp"

int main() {
	readToProgram(accounts);

	int choice;
	bool quit{false};
	long long accountNumber;

	do {
		std::cout << "1 - Deposit amount" << std::endl
				  << "2 - Withdraw amount" << std::endl
				  << "3 - Check balance" << std::endl
				  << "4 - Exit program" << std::endl << std::endl
				  << "Enter your choice: ";
		std::cin >> choice;

		std::cout << std::endl;

		switch (choice) {
			case 1:
				std::cout << "Enter your account number: ";
				std::cin >> accountNumber;

				depositAmount(accountNumber);
				refreshScreen();
				break;

			case 2:
				std::cout << "Enter your account number: ";
				std::cin >> accountNumber;

				withdrawAmount(accountNumber);
				refreshScreen();
				break;

			case 3:
				std::cout << "Enter your account number: ";
				std::cin >> accountNumber;

				displayBalance(accountNumber);
				refreshScreen();
				break;

			case 4:
				quit = true;
				break;

			default:
				std::cout << "Invalid choice! Try again";
				refreshScreen();
		}
	} while (!quit);

	writeInFile(accounts);

	std::cout << std::endl;
	return 0;
}