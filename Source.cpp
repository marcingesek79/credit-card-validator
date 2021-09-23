// Validator for Visa cards. Number must start with a 4 and have 16 digits.
#include<iostream>
#include<string>

int calculateCheckDigit(std::string creditCardNumber, int* checkDigit) {
	int creditCardNumberLen = creditCardNumber.length() - 1;
	*checkDigit = std::stoi(std::string(1, creditCardNumber[creditCardNumberLen]));
	creditCardNumber.pop_back();

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

	return (10 - (sum % 10)) % 10;
}

void checkIsValid(int checkDigit, int calculatedCheckDigit) {
	if (checkDigit == calculatedCheckDigit) {
		std::cout << "Number is valid." << std::endl;
	}
	else {
		std::cout << "Number is not valid." << std::endl;
	}
}

int main() {
	int checkDigit = NULL;
	std::string creditCardNumber = "";
	std::cout << "Please, enter your number: ";
	std::cin >> creditCardNumber;
	checkIsValid(checkDigit, calculateCheckDigit(creditCardNumber, &checkDigit));
}