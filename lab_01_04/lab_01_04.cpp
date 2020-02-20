#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: lab_01_04.exe <input file> <output file> <searchString> <replacementString>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

struct FilesArgs
{
	std::ifstream input;
	std::ofstream output;
};

std::optional<FilesArgs> InitInputOutputFiles(const std::optional<Args>& args)
{
	FilesArgs filesArgs;
	filesArgs.input.open(args->inputFileName);
	if (!filesArgs.input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return std::nullopt;
	}

	filesArgs.output.open(args->outputFileName);
	if (!filesArgs.output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return std::nullopt;
	}
	return filesArgs;
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(std::ifstream& input, std::ofstream& output, std::optional<Args>& args)
{
	std::string line;

	while (std::getline(input, line))
	{
		if (args->searchString.empty())
		{
			output << line << "\n";
		}
		else
		{
			output << ReplaceString(line, args->searchString, args->replaceString) << "\n";
		}
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	auto filesArgs = InitInputOutputFiles(args);
	if (!filesArgs)
	{
		return 1;
	}

	CopyFileWithReplace(filesArgs->input, filesArgs->output, args);

	if (filesArgs->input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return 1;
	}

	if (!filesArgs->output.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to write data to output file\n";
		return 1;
	}

	return 0;
}
