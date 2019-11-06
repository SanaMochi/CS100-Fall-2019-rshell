#include <iostream>
#include <string>
#include "../header/parser.h"

int main(){
	std::string input = "";
	std::string test = "geany f1 || ls -a ./ ; gedit -s f2";
	char money = '$';
	Parser p;
	/*
	while(input == "\n" || input == ""){
		std::cout << money;
		std::getline(std::cin, input);
	}
	p.getInput(input);
	*/
	p.getInput(test);
	p.parse();
	std::cout << "print commands: " ;p.printCommands();
	std::cout << "Parse FName: " ;p.parseFileNames();
	p.parseArguments();
	std::cout << "\nParse argv: ";p.printArguments();
	std::cout << "Format fName @ 1: " << p.formatFileName(0);
	std::cout << "\nFormat Argument @ 1: " << *(p.formatArguments(2));
	//p.deletePointer();
	return 0;
}
