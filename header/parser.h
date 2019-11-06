#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <iostream>


class Parser{
	std::string command;
	std::string space = " ";
	std::string and_symbol = "&&";
	std::string or_symbol = "||";
	std::string end_symbol = ";";
	std::vector<std::string> commands;
	std::vector<std::string> to_run;
	std::vector<std::string> fileNames;
	std::vector<std::string> argv;
	char ** pointer;
	int pointerSize;
	
	public:
	Parser();
	Parser(std::string s);
	
	void getInput(std::string s);
	void print();
	
	std::vector<std::string> parse();
	void printCommands();
	std::vector<std::string> getCommandsToRun();
	
	void parseFileNames();
	void parseArguments();
	void printArguments();
	
	const char* formatFileName(int location);
	char ** formatArguments(int location);
	
	void deletePointer();
};
#endif
