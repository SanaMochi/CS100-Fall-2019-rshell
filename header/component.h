#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>
#include <vector>
#include <iostream>
//#include "parser.h"
//#include "command.h"

class Component{
// bool test_bool = false; 
	public:
	const std::string space = " ";			//
	const std::string and_symbol = "&&";		//probably dont need these, but I thought the code would look nicer with 
	const std::string or_symbol = "||";		//	hard coded values
	const std::string end_symbol = ";";		//
	const std::string open_bracket = "[";
	const std::string closed_bracket = "]";
	char quotation_mark = '\"';
	const std::string opening_parens = "(";
	const std::string closing_parens = ")";
	const std::string test_obj = "test";

//	std::vector<std::string> pattern; 	//stores the seperators in order
	std::vector<std::string> commands;	//stores the initial string, but broken up by space charecters
	std::vector<std::string> to_run;	//stores and combines the strings from commands, but broken up by '||' , '&&' , ';'
	std::vector<std::string> fileNames; //stores only the file name of each program to be run
	std::vector<std::string> argv;		//stores only the arguments for each program, seperates diffrent arguments by '???' to signify that the next arguments are to by run by a diffrent program
										//e.g. fileNames.print == ls , geany , mkdir
										//e.g argv.print == -a , ../ , ??? , file1.txt , ??? -r , folder1
										//					^^^^^^^          ^^^^^^^^^			^^^^^^^^
										//				run with ls			run with geany		run with mkdir

	char ** pointer;			//stores the pointer to the arguments to run, should probably delete dynamically allocate pointers?
	int pointerSize;				//stores how many pointers deep the 2d array is, help with deleting?

//	int status;
//	int err;
  
	std::vector<std::string> pattern; 	//stores the seperators in order	
	int numOfCommands;
	bool exit_bool = false;
	bool test_bool = false;			//if test returns true of false;
	std::string command;				//used to store the whole command entered as a string

	~Component();					// deallocates dynamially made pointers 
	virtual char** formatArguments(int location);
	virtual void removeNextCommand(int location);	//removes the next command e.g. it failed with ||

	bool getTestBool();	
	void setTestTrue();
	void setTestFalse();
	void resetVectors();
	bool shouldIExit();
	void shouldIExit(bool shouldI);
	
	virtual void runCommand(char ** argv) = 0;
	virtual void runAll(int numOfCommands, Component* parser) = 0;
};
#endif
