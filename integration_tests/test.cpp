#include <iostream>
#include <string>
#include "../header/test.h"
#include "../header/parser.h"
#include "../header/command.h"
#include "../header/component.h"

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
			std::getline(std::cin, input);
		}
	p.getInput(input);
	if(input == "exit" || p.shouldIExit()){
		return 0;
	}
	p.parse();
	input = "";
	c->runAll(p.getSize(), &p);
	if(argc > 1)
		return 0;
}
	return 0;
}
