#include "ManagerOperations.hpp"

int main() {
	readToProgram(accounts);

	int choice;
	bool quit{false};

	do {
		std::cout << "1 - Open an account" << std::endl
				  << "2 - Get number of account" << std::endl
				  << "3 - Display all accounts" << std::endl
				  << "4 - Close an account" << std::endl
				  << "5 - Exit program" << std::endl << std::endl
				  << "Enter your choice: ";
		std::cin >> choice;

		std::cout << std::endl;

		switch (choice) {
			case 1:
				if (openAccount(accounts))
					std::cout << "Account opened successfully" << std::endl;
				else
					std::cout << "Failed to open account" << std::endl;

				refreshScreen();
				break;

			case 2:
				displayNumberOfAccounts();
				refreshScreen();
				break;

			case 3:
				displayAllAccounts(accounts);
				refreshScreen();
				break;

			case 4:
				if (closeAccount(accounts))
					std::cout << "Account closed successfully" << std::endl;
				else
					std::cout << "Failed to close account" << std::endl;

				refreshScreen();
				break;

			case 5:
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