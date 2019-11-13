#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <iostream>
#include "component.h"


class Parser: public Component {
	int status = 0;
	int err = 0;
	public:
	//int numOfCommands;
	//bool exit = false;
	//std::string command;				//used to store the whole command entered as a string
	const std::string space = " ";			//
	const std::string and_symbol = "&&";		//probably dont need these, but I thought the code would look nicer with 
	const std::string or_symbol = "||";		//	hard coded values
	const std::string end_symbol = ";";		//
/*	std::vector<std::string> pattern; 	//stores the seperators in order
	std::vector<std::string> commands;	//stores the initial string, but broken up by space charecters
	std::vector<std::string> to_run;	//stores and combines the strings from commands, but broken up by '||' , '&&' , ';'
	std::vector<std::string> fileNames; //stores only the file name of each program to be run
	std::vector<std::string> argv;		//stores only the arguments for each program, seperates diffrent arguments by '???' to signify that the next arguments are to by run by a diffrent program
										//e.g. fileNames.print == ls , geany , mkdir
										//e.g argv.print == -a , ../ , ??? , file1.txt , ??? -r , folder1
										//					^^^^^^^          ^^^^^^^^^			^^^^^^^^
										//				run with ls			run with geany		run with mkdir
	char ** pointer;					//stores the pointer to the arguments to run, should probably delete dynamically alocated pointers?
	int pointerSize;					//stores how many pointers deep the 2d array is, help with deleting?
*/	
	//public:
	Parser();
	Parser(std::string s);
	
	void getInput(std::string s);		//get the input from user and store it
	void print();						//print input, mainly used for testing
	
	void parse();						//parse the input string and makes a vector of words broken up by spaces, and by seperators ,that gets stored in commands and to_run respectivly
	void printCommands();				//print commands, mainly used for testing
	std::vector<std::string> getCommandsToRun(); //get to_run, mainly used for testing
	
	void parseFileNames();				//seperates out the file names from to_run and stores them in fileNames
	void parseArguments();				//seperates out the arguments from to_run and stores them in argv
/*	void printArguments();				//print the arguments, mainly used for testing
	void printFileNames();
	void printPattern();
	*/
	
/*	const char* formatFileName(int location);	//get the file name at a location and return it to be run with execvp
	char ** formatArguments(int location);		//get the argument(s) that go with the file name at a location and retrun them to be run with execvp
								//was thinking we could make a loop with execvp()
								//when we figure out how to implement the logic of
								//the seperators '||' , '&&' , ';'
								//eg for(int i = 0; i < fileNames.size(); i++)
								//		execvp(formatFileName(i), formatArguments(i))
	
	void resetVectors();		//resets all vectors to empty, incase multiple lines of commands are typed
	void preParse(); 			//look for comments or exit
	void removeNextCommand(int location);	//removes the next command e.g. it failed with ||
	bool shouldIExit();
	void shouldIExit(bool shouldI);
*/
	int getSize(); 				//get total number of commands to execute
	
	virtual void runCommand(char ** argv);
	virtual void runAll(int numOfCommands, Component* parser);
	
	void deletePointer();		//TO-DO
};
#endif
