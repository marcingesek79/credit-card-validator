/* 
	Requirements for validation:
		1) Visa: Number must start with a 4 and have 13-16-19 digits.
		2) Mastercard: Number must start with 51, 52, 53, 54, 55 or 222100-272099 and have 16 digits
		3) Visa Electron: Number must start with 4026, 417500, 4508, 4844, 4913 or 4917 and have 16 digits
		4) American Express: Number must start with 34 or 37 and have 15 digits.
*/

#include <iostream>
#include <string>

enum class CardType : int
{
	VISA = 1,
	MASTERCARD,
	VISA_ELECTRON,
	AMERICAN_EXPRESS
};

int getDigit(const std::string& number, int position)
{
	return number.at(position) - '0';
}

bool isStringNumerical(const std::string& number)
{
	for (auto& c : number)
	{
		if (!std::isdigit(c))
			return false;
	}
	return true;
}

// Checks if this is a visa card number
bool isVisa(const std::string& credit_card_number) {
	const int prefix = std::stoi(credit_card_number.substr(0, 1));
	if ((credit_card_number.length() == 13 ||
		credit_card_number.length() == 16 ||
		credit_card_number.length() == 19) && 
		prefix == 4)
	{
		return true;
	}
	return false;
}

// Checks if this is a mastercard card number
bool isMastercard(const std::string& credit_card_number) {
	const int prefix = std::stoi(credit_card_number.substr(0, 2));
	const int long_prefix = std::stoi(credit_card_number.substr(0, 6));
	if (credit_card_number.length() == 16 &&
		((prefix >= 51 && prefix <= 55) || (long_prefix >= 222100 && long_prefix <= 272099)))
	{
		return true;
	}
	return false;
}

// Checks if this is a visa electron card number
bool isVisaElectron(const std::string& credit_card_number) {
	const int prefix = std::stoi(credit_card_number.substr(0, 4));
	const int long_prefix = std::stoi(credit_card_number.substr(0, 6));
	if (credit_card_number.length() == 16 && 
		(prefix == 4026 || prefix == 4508 ||
		prefix == 4844 || prefix == 4913 ||
		prefix == 4917 || long_prefix == 417500)) 
	{
		return true;
	}
	return false;
}

// Checks if this is a American Express card number
bool isAmericanExpress(const std::string& credit_card_number) {
	const int prefix = std::stoi(credit_card_number.substr(0, 2));
	if (credit_card_number.length() == 15 && (prefix == 34 || prefix == 37))
	{
		return true;
	}	
	return false;
}

// Validates the last digit of the number using Luhn's algorithm.
bool isNumberValid(const std::string& credit_card_number)
{
	const int length = credit_card_number.length();
	
	int sum = 0;
	int parity = length % 2;
	for (size_t i{}; i < length - 1; i++)
	{
		int digit = getDigit(credit_card_number, i);
		if (i % 2 != parity)
			sum += digit;
		else if (digit > 4)
			sum += 2 * digit - 9;
		else
			sum += 2 * digit;
	}

	const int last_digit = (10 - (sum % 10)) % 10;
	return last_digit == getDigit(credit_card_number, length - 1);
}

bool isTypeValid(const std::string& credit_card_number, CardType type)
{
	bool is_type_valid;

	switch (type) 
	{
		case CardType::VISA :
			is_type_valid = isVisa(credit_card_number);
			break;
		case CardType::MASTERCARD :
			is_type_valid = isMastercard(credit_card_number);
			break;
		case CardType::VISA_ELECTRON :
			is_type_valid = isVisaElectron(credit_card_number);
			break;
		case CardType::AMERICAN_EXPRESS :
			is_type_valid = isAmericanExpress(credit_card_number);
			break;
	}

	return is_type_valid;
}

void handleInput(CardType card_type)
{
	std::string credit_card_number {};
	std::cout << "Please, enter credit card number: ";
	std::cin >> credit_card_number;

	//todo: check for letters in number
	if (std::cin.fail() || !isStringNumerical(credit_card_number))
	{
		std::cout << "Invalid input" << std::endl;
		return;
	}

	if (!isTypeValid(credit_card_number, card_type))
	{
		std::cout << "This card number does not belong to this type" << std::endl;
		return;
	}

	if (isNumberValid(credit_card_number))
		std::cout << "This card number is valid" << std::endl;
	else
		std::cout << "This card number is invalid" << std::endl;
}

void getInput() 
{
	int choice {};
	std::cout << "What card do you want to validate?" << std::endl;
	std::cout << "1) Visa" << std::endl;
	std::cout << "2) Mastercard" << std::endl;
	std::cout << "3) Visa Electron" << std::endl;
	std::cout << "4) American Express" << std::endl;
	std::cout << "0) Exit" << std::endl;
	std::cout << "Your choice: ";
	std::cin >> choice;
	std::cout << std::endl;

	if (!std::cin.fail() && choice > 0 && choice <= 4)
	{
		CardType card_type = static_cast<CardType>(choice);
		handleInput(card_type);
	}
	else if (choice == 0)
		return;
	else
		std::cout << "Invalid input." << std::endl;
}

int main(int argc, char* argv[]) 
{
	getInput();
	return 0;
}
