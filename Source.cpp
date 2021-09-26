/* 
Author: Marcin Gesek - marcin.gesek79@gmail.com
Title: Validator for credit cards.
Description:
	Requirements for validation:
		1) Visa: Number must start with a 4 and have 13-16-19 digits.
		2) Mastercard: Number must start with 51, 52, 53, 54, 55 or 222100-272099 and have 16 digits
		3) Visa Electron: Number must start with 4026, 417500, 4508, 4844, 4913 or 4917 and have 16 digits
*/

#include<iostream>
#include<string>
#define NUM_OF_TYPES 3


// Calculates the last digit of the number using Luhn's algorithm.
int calculateCheckDigit(std::string creditCardNumber, int* checkDigit) {
	int creditCardNumberLen = creditCardNumber.length() - 1;
	// Drops the last digit and saves it
	*checkDigit = std::stoi(std::string(1, creditCardNumber[creditCardNumberLen]));
	creditCardNumber.pop_back();

	// Luhn algorithm
	int sum = 0;
	int nextToMultiple = creditCardNumberLen - 1;
	for (int i = creditCardNumberLen - 1; i >= 0; i--)
	{
		int currentDigit = std::stoi(std::string(1, creditCardNumber[i]));
		if (i == nextToMultiple) {
			currentDigit *= 2;
			if (currentDigit > 9) currentDigit -= 9;
			nextToMultiple -= 2;
		}
		sum += currentDigit;
	}

	// Returns calculated last digit
	return (10 - (sum % 10)) % 10;
}

// Checks if the calculated digit and entered digit are the same
void checkIsValid(int checkDigit, int calculatedCheckDigit) {
	if (checkDigit == calculatedCheckDigit) {
		std::cout << "Number is valid." << std::endl;
	}
	else {
		std::cout << "Number is not valid." << std::endl;
	}

	std::cout << std::endl;
}

// Checks if this is a visa card number
bool checkIsVisa(std::string creditCardNumber) {
	if ((creditCardNumber.length() == 13 ||
		creditCardNumber.length() == 16 ||
		creditCardNumber.length() == 19) && std::stoi(std::string(1, creditCardNumber[0])) == 4) {
		return true;
	}
	std::cout << "This is not a Visa card." << std::endl << std::endl;
	return false;
}

// Checks if this is a mastercard card number
bool checkIsMastercard(std::string creditCardNumber) {
	int numberPrefix = std::stoi(creditCardNumber.substr(0, 2));
	int longNumberPrefix = std::stoi(creditCardNumber.substr(0, 6));
	if (creditCardNumber.length() == 16) {
		if ((numberPrefix >= 51 && numberPrefix <= 55) || (longNumberPrefix >= 222100 && longNumberPrefix <= 272099)) {
			return true;
		}
	}
	std::cout << "This is not a Mastercard card." << std::endl << std::endl;
	return false;
}

// Checks if this is a visa electron card number
bool checkIsVisaElectron(std::string creditCardNumber) {
	int numberPrefix = std::stoi(creditCardNumber.substr(0, 4));
	int longNumberPrefix = std::stoi(creditCardNumber.substr(0, 6));
	if (creditCardNumber.length() == 16) {
		if (numberPrefix == 4026 || numberPrefix == 4508 ||
			numberPrefix == 4844 || numberPrefix == 4913 ||
			numberPrefix == 4917 || longNumberPrefix == 417500) return true;
	}
	std::cout << "This is not a Visa Electron card." << std::endl << std::endl;
	return false;
}

void validateCard(int cardType) {
	int checkDigit;
	std::string creditCardNumber = "";

	std::cout << "Please, enter your number: ";
	std::cin >> creditCardNumber;

	switch (cardType) {
	case 1:
		// Visa
		if (!checkIsVisa(creditCardNumber)) return;
		break;
	case 2:
		// Mastercard
		if (!checkIsMastercard(creditCardNumber)) return;
		break;
	case 3:
		// Visa Electron
		if (!checkIsVisaElectron(creditCardNumber)) return;
		break;
	}

	checkIsValid(checkDigit, calculateCheckDigit(creditCardNumber, &checkDigit));
}

// Shows menu and handles input
void inputMenu() {
	int choice;
	
	while (true) {
		std::cout << "What card do you want to validate?" << std::endl;
		std::cout << "1) Visa" << std::endl;
		std::cout << "2) Mastercard" << std::endl;
		std::cout << "3) Visa Electron" << std::endl;
		std::cout << "0) Exit" << std::endl;
		std::cout << "Your choice: ";
		std::cin >> choice;
		std::cout << std::endl;

		if (choice > 0 && choice <= NUM_OF_TYPES) {
			validateCard(choice);
		}
		else break;
	}
}

int main() {
	inputMenu();
}