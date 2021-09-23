// Validator for Visa cards. Number must start with a 4 and have 13-16-19 digits.
#include<iostream>
#include<string>

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
}

// Checks if this is a visa card number
bool checkIsVisa(std::string creditCardNumber) {
	if ((creditCardNumber.length() == 13 ||
		creditCardNumber.length() == 16 ||
		creditCardNumber.length() == 19) && std::stoi(std::string(1, creditCardNumber[0])) == 4) {
		return true;
	}
	else return false;
}

int main() {
	// Input
	int checkDigit = NULL;
	std::string creditCardNumber = "";
	std::cout << "Please, enter your number: ";
	std::cin >> creditCardNumber;
	
	if (checkIsVisa(creditCardNumber)) {
		checkIsValid(checkDigit, calculateCheckDigit(creditCardNumber, &checkDigit));
	}
	else {
		std::cout << "This is not a visa card." << std::endl;
	}
	
}