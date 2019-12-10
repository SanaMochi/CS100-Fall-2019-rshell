#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
//#include "parser.h"
#include "component.h"
//#include "test.h"

class Test;
class Parser;
class Command : public Component{
	int test_return;
	protected:
	char** command;
	Component* nextCommand;			//makes this class a composite
	int status;
	int err;
	Test* test;
	
	public:
	Command();	
	virtual void runCommand(char ** argv);
<<<<<<< HEAD
	virtual void runAll(int numOfCommands, Component* parser);
	void OverwriteOutNew(std::string to_run_command, int i, Component* parser);
	void OverwriteOut(std::string to_run_command, int i, Component* parser);
	void OverwriteIn(std::string to_run_command, int i, Component* parser);
	void Piping(std::string to_run_command, int i, Component* parser);
//	void parseNoParens(std::string comm);
=======
	
	virtual void runAll(int numOfCommands, Component* parser);
	//void makeList(int numOfCommands, Parser* parser);
	
>>>>>>> ecf77f3dd78e4635d76419e175f1399c0460be2d
};

#endif
