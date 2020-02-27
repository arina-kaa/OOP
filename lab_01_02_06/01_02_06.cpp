#include <iostream>
#include <fstream>
#include <optional>
#include <string>

int CharToDigit(const char& ch, const int& radix, bool& wasError)
{
	int digit = -1;
	if (ch >= '0' && ch <= '9')
	{
		digit = ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		digit = ch - 'A' + 10;
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		digit = ch - 'a' + 10;
	}
	if (digit < 0 || digit >= radix)
	{
		wasError = true;
		std::cout << "Wrong char in current notation!\n";
	}
	return (int)digit;
}

char DigitToChar(const int& digit, const int& radix, bool& wasError)
{
	char result = '\0';
	if (digit >= 0 && digit <= 9)
	{
		result = (char)('0' + digit);
	}
	if (digit < radix && digit >= 10)
	{
		result = (char)('A' - 10 + digit);
	}
	if (result == '\0')
	{
		wasError = true;
	}
	return result;
}

int StringToInt(const std::string& str, const int& radix, bool& wasError)
{
	unsigned int result = 0;
	const int sign = (str[0] == '-') ? -1 : 1;
	const int firstDigitPosition = (sign == -1) ? 1 : 0;
	
	for (size_t i = firstDigitPosition; i < str.length(); ++i)
	{
		unsigned int digit = CharToDigit(str[i], radix, wasError);
		// checking limits
		if (result <= (INT_MAX - digit + firstDigitPosition) / radix)
		{
			result = radix * result + digit;
		}
		else
		{
			wasError = true;
			std::cout << "Value is out of limit!\n";
			return 0;
		}
	}
	return (int)sign * result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	std::string resultStr = "";
	bool isNegative = n < 0; // save sign of numbers
	unsigned int number = abs(n);

	if (number == 0)
	{
		resultStr = "0";
	}

	unsigned long remainder;
	while (number > 0)
	{
		remainder = number % radix;
		number = number / radix;
		char nextCh = DigitToChar(remainder, radix, wasError);
		resultStr.push_back(nextCh);
	};
	if (isNegative) resultStr.push_back('-');
	std::reverse(resultStr.begin(), resultStr.end());

	return resultStr;
}

bool IsValidNotation(const int& notation)
{
	const int MIN_ALLOWED_NOTATION = 2;
	const int MAX_ALLOWED_NOTATION = 36;
	return notation >= MIN_ALLOWED_NOTATION && notation <= MAX_ALLOWED_NOTATION;
}

struct Args
{
	int sourceNotation;
	int destinationNotation;
	int value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	const int COMMON_NOTATION = 10;
	bool wasError = false;
	if (argc != 4)
	{
		std::cout << "Invalid arguments count.\n"
			<< "Usage: lab_01_02_06.exe <source notation> <destination notation> <value>.\n";
		return std::nullopt;
	}

	Args args;
	args.sourceNotation = StringToInt(argv[1], COMMON_NOTATION, wasError);
	args.destinationNotation = StringToInt(argv[2], COMMON_NOTATION, wasError);
	if (!IsValidNotation(args.sourceNotation) || !IsValidNotation(args.destinationNotation))
	{
		std::cout << "Notations must be between 2 and 36 value.\n";
		return std::nullopt;
	}
	args.value = StringToInt(argv[3], args.sourceNotation, wasError);
	if (wasError)
	{
		std::cout << "Invalid arguments values.\n";
		return std::nullopt;
	}

	return args;
}



bool Radix(const int& value, const int& destinationNotation)
{
	bool wasError = false;
	std::string resultStr = IntToString(value, destinationNotation, wasError);
	if (!wasError)
	{
		std::cout << resultStr << "\n";
	}

	return !wasError;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool result = Radix(args->value, args->destinationNotation);

	return (result) ? 0 : 1;
}
