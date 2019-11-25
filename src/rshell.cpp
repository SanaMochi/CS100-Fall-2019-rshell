#include <iostream>
#include <string>
#include "../header/parser.h"
#include "../header/command.h"
#include "../header/component.h"
#include "../src/parser.cpp"
#include "../src/command.cpp"
#include "../src/component.cpp"

int main(int argc, char *argv[]){
	std::string input = "";
	std::string test = "geany f1 || ls -a ./ -a ../ ; gedit -s f2";
	char money = '$';
	Parser p;
	Component* c = new Command();
	
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			input += argv[i];
			input += " ";
		}
	}
	
	while(input != "exit"){
		
		while(input == "\n" || input == ""){
			std::cout << money;
			//std::cout << "lets go bucko";
			std::getline(std::cin, input);
		}
	p.getInput(input);
	//std::cout << "\nInput: " << input <<"\n";
	if(input == "exit" || p.shouldIExit()){
		return 0;
	}
	//p.getInput(test);
	p.parse();				//
	//std::cout << "input: " << p.command;
	input = "";
	//p.parseFileNames();		//could probably combine all 3 into 1 because they all need to be run
	//p.parseArguments();		//
	
	//for testing
	//std::cout << "\nPrint commands: "; p.printCommands();
	//std::cout << "\nPrint arguments: ";p.printArguments();
	//std::cout << "\nFile 1: " << p.formatFileName(0);
	//std::cout << "\nArgument 1: " << *(p.formatArguments(0));
	

	//c->runCommand(p.formatArguments(0));
	//std::cout << "\nPrint commands: "; p.printCommands();
	//std::cout << "\nPrint pattern: "; p.printPattern();
	c->runAll(p.getSize(), &p);
	/*
	std::cout << "\nPrint args: "; p.printArguments();
	p.removeNextCommand(1);
	std::cout << "\nPrint args: "; p.printArguments();
	* */
	//std::cout << "input: " << input;
	//std::cout << std::endl;
	if(argc > 1)
		return 0;
}
	return 0;
}
