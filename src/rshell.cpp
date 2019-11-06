#include <iostream>
#include <string>
#include "../header/parser.h"

int main(){
	std::string input = "";
	char money = '$';
	Parser p;
	
	while(input == "\n" || input == ""){
		std::cout << money;
		std::getline(std::cin, input);
	}
	p.getInput(input);
	p.parse();
	std::cout << "print commands: " ;p.printCommands();
	std::cout << "Parse FName: " ;p.parseFileNames();
	std::cout << "Parse argv: ";p.printArguments();
	return 0;
}
