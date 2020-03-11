#include <iostream>
#include <fstream>
#include <optional>
#include <string>

const int MAX_LENGTH = 255;

enum mode {
	UNDEFINED_MODE,
	PACK_MODE,
	UNPACK_MODE
};

struct Args
{
	mode currentMode;
	std::string inputFileName;
	std::string outputFileName;
};

mode getCurrentMode(const std::string& modeStr)
{
	mode currentMode = UNDEFINED_MODE;
	if (modeStr == "pack") 
	{ 
		currentMode = PACK_MODE; 
	}
	else if (modeStr == "unpack") 
	{ 
		currentMode = UNPACK_MODE; 
	}

	return currentMode;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	bool wasError = false;
	if (argc != 4)
	{
		std::cout << "Invalid arguments count.\n"
			<< "Usage: lab_01_04_01.exe pack <input file> <output file> or lab_01_04_01.exe unpack <input file> <output file>.\n";
		return std::nullopt;
	}

	Args args;

	args.currentMode = getCurrentMode(argv[1]);
	if (args.currentMode == UNDEFINED_MODE)
	{
		std::cout << "Invalid mode.\n"
			<< "Usage: pack or unpack.\n";
		return std::nullopt;
	}
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}

void PrintPackResult(std::ostream& output, const int symbolCount, const char symbol)
{
	output << (char)symbolCount << symbol;
}

void PackFile(std::istream& input, std::ostream& output)
{
	char currentSymbol;
	char originalSymbol;
	int originalSymbolCount = 0;

	while (input.get(currentSymbol))
	{
		if (originalSymbolCount == 0)
		{
			originalSymbol = currentSymbol;
		}

		if (originalSymbol == currentSymbol)
		{
			originalSymbolCount++;
		}
		
		if (originalSymbol != currentSymbol || originalSymbolCount == MAX_LENGTH)
		{
			PrintPackResult(output, originalSymbolCount, originalSymbol);
			originalSymbol = currentSymbol;
			originalSymbolCount = (originalSymbolCount == MAX_LENGTH) ? 0 : 1;
		}
	}

	if (originalSymbolCount != 0)
	{
		PrintPackResult(output, originalSymbolCount, originalSymbol);
	}
}

void UnpackFile(const std::istream& input, std::ostream& output)
{

}

bool HandleFileByMode(const mode currentMode, const std::string& inputFileName, std::string& outputFileName)
{
	bool result = true;
	std::ifstream input;
	std::ofstream output;

	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		result = false;
	}

	output.open(outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		result = false;
	}

	switch (currentMode)
	{
	case PACK_MODE:
		PackFile(input, output);
		break;
	case UNPACK_MODE:
		UnpackFile(input, output);
		break;
	default:
		break;
	}

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		result = false;
	}

	if (!output.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to write data to output file\n";
		result = false;
	}

	return result;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool result = HandleFileByMode(args->currentMode, args->inputFileName, args->outputFileName);

	return (result) ? 0 : 1;
}