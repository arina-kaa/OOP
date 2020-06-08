#include "CSession.h"

int main()
{
	CSession session;
	session.ProcessCommand(std::cin);

	std::cout << "Shape with max area:" << std::endl;
	std::cout << session.GetMaxAriaShape()->ToString();
	std::cout << "Shape with min perimeter:" << std::endl;
	std::cout << session.GetMinPerimeterShape()->ToString();

	return 0;
}