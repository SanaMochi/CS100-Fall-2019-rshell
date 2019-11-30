#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "component.h"
//#include "command.h"
//#include "test.h"

class Component;
class Command;
class Parser: public Component {
	int status = 0;
	int err = 0;
	std::vector<int> opened_parens;
	std::vector<int> closed_parens;

	public:
	Parser();
	Parser(std::string s);
	
	void getInput(std::string s);		//get the input from user and store it
	void print();						//print input, mainly used for testing
	
	void parse();						//parse the input string and makes a vector of words broken up by spaces, and by seperators ,that gets stored in commands and to_run respectivly
	void printCommands();				//print commands, mainly used for testing
	std::vector<std::string> getCommandsToRun(); //get to_run, mainly used for testing
	
	void parseFileNames();				//seperates out the file names from to_run and stores them in fileNames
	void parseArguments();				//seperates out the arguments from to_run and stores them in argv
	void printArguments();				//print the arguments, mainly used for testing
	void printFileNames();
	void printPattern();
	
	const char* formatFileName(int location);	//get the file name at a location and return it to be run with execvp
	void preParse(); 			//look for comments or exit
//	bool shouldIExit();
//	void shouldIExit(bool shouldI);

	int getSize(); 				//get total number of commands to execute
	
	virtual void runCommand(char ** argv);
	virtual void runAll(int numOfCommands, Component* parser);
	
	void deletePointer();		//We don't dynamically allocate memory, so I don't think we need it
};
#endif
