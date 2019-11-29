#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <iostream>
#include "parser.h"
#include <vector>
#include "component.h"
#include <unistd.h>

class Command : public Component{
	
	public:
	Command();
	virtual void runCommand(char ** argv);
	void outputRedirection(std::string str);
	void outputRedirectionAppend(std::string str);
	void inputRedirection(std::string str);
	void pipe(std::string str);
	int countArgs(char ** argv);
	int getLenght(char ** argv, int i);
	virtual void runAll(int numOfCommands, Parser* parser);
	//void makeList(int numOfCommands, Parser* parser);
	
};

#endif
