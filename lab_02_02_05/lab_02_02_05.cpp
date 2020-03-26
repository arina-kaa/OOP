#include "DecodeHtml.h"

int main()
{
	std::string htmlStr;
	while (std::getline(std::cin, htmlStr))
	{
		std::cout << DecodeHtml(htmlStr) << std::endl;
	}
	return 0;
}