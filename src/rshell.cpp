#include <iostream>
#include <string>
#include "../header/parser.h"
#include "../header/command.h"
//#include <unistd.h>

int main(){
	std::string input = "";
	std::string test = "geany f1 || ls -a ./ -a ../ ; gedit -s f2";
	char money = '$';
	Parser p;
	Command c;
	
	while(input == "\n" || input == ""){
		std::cout << money;
		std::getline(std::cin, input);
	}
	p.getInput(input);
	
	//p.getInput(test);
	p.parse();				//
	p.parseFileNames();		//could probably combine all 3 into 1 because they all need to be run
	p.parseArguments();		//
	
	//for testing
	//std::cout << "\nPrint commands: "; p.printCommands();
	//std::cout << "\nPrint arguments: ";p.printArguments();
	//std::cout << "\nFile 1: " << p.formatFileName(0);
	//std::cout << "\nArgument 1: " << *(p.formatArguments(0));
	
	c.runCommand(p.formatFileName(0), p.formatArguments(0));
	std::cout << std::endl;
	return 0;
}
