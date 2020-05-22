#include "UrlParser.h"

std::optional<Args> GetUrlFromInput(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count." << std::endl;
		std::cout << "Usage: lab_02_05_01.exe <your url>." << std::endl;
		return std::nullopt;
	}
	Args url;
	try
	{
		url.value = argv[1];
		return url;
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::smatch matches;
	std::regex  urlRegex("^((http|https|ftp)?:\/\/)?([^\/@: ]+)(:[0-9]{1,5})?([^ ]*)?");

	if (std::regex_search(url, matches, urlRegex)) 
	{
		std::cout << matches.str(1) << std::endl;
		std::cout << matches.str(2) << std::endl;
		std::cout << matches.str(3) << std::endl;
		std::cout << matches.str(4) << std::endl;
		std::cout << matches.str(5) << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}