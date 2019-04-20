#include "TUI.h"
#include<iostream>
#include<string.h>

using namespace WorldArchitect;


/// \function requestInt
/// \brief requests an integer from the user
int TUI::requestInt(std::string name)
{
	int response;
	std::cout << "Please input an integer value for " << name << ": ";
	std::cin >> response;
	return response;
}


/// \function requestString
/// \brief requests a string from the user
std::string TUI::requestString(std::string name)
{
	std::string response;
	std::cout << "Please input a string value for " << name << ": ";
	std::cin >> response;
	return response;
}

double TUI::requestDouble(std::string paramName)
{
	double response;
	std::cout << "Please input a double value for " << paramName << ": ";
	std::cin >> response;
	return response;
}

void TUI::init()
{
}
