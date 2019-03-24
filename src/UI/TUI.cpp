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
char *TUI::requestString(std::string name)
{
	std::string response;
	std::cout << "Please input a string value for " << name << ": ";
	std::cin >> response;
	char *cstr = new char[response.length() + 1];
	strcpy(cstr, response.c_str());
	return cstr;
}
