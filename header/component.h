#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>
#include <vector>
#include <iostream>
//#include "parser.h"
//#include "command.h"

class Component{
//	std::vector<std::string> pattern;
	protected:
//	Component* nextCommand;
//	char** command;				//moved to command class so composite pattern (idk how much it changes things, I'll see if it works
	std::vector<std::string> pattern; 	//stores the seperators in order
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

	public:
	int numOfCommands;
	bool exit = false;
	std::string command;				//used to store the whole command entered as a string

	std::string getPattern(int i);
/*	void printArguments();
	void printFileNames();
	void printPattern();
	const char* formatFileName(int location);
*/	char** formatArguments(int location);
/*
	void resetVectors();
	void preParse();
*/	void removeNextCommand(int location);
/*	bool shouldIExit();
	void shouldIExit(bool shouldI);
*/
	virtual int getSize();
	
	virtual void runCommand(char ** argv) = 0;
	virtual void runAll(int numOfCommands, Component* parser) = 0;
};
#endif
