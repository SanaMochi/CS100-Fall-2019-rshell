#include <iostream>
#include <string>
#include "../header/parser.h"
#include "../header/command.h"


int main(){
	std::string input = "";
	std::string test = "geany f1 || ls -a ./ -a ../ ; gedit -s f2";
	char money = '$';
	Parser p;
	Component* c = new Command();
	
	while(input != "exit"){
		while(input == "\n" || input == ""){
			std::cout << money;
			std::getline(std::cin, input);
		}
	p.getInput(input);
	
	//p.getInput(test);
	p.parse();				//
	//p.parseFileNames();		//could probably combine all 3 into 1 because they all need to be run
	//p.parseArguments();		//
	
	//for testing
	//std::cout << "\nPrint commands: "; p.printCommands();
	//std::cout << "\nPrint arguments: ";p.printArguments();
	//std::cout << "\nFile 1: " << p.formatFileName(0);
	//std::cout << "\nArgument 1: " << *(p.formatArguments(0));
	

	// c->runCommand(p.formatArguments(0));
	c->runAll(p.getSize(), &p);
	
	std::cout << std::endl;
	if(input == "exit")
		return 0;
	input = "";
}
	return 0;
}
