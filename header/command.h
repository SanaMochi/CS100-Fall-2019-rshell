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
//	void removeNextCommand(int location);
	
	virtual void runCommand(char ** argv);
	
	virtual int runAll(int numOfCommands, Component* parser);
	//void makeList(int numOfCommands, Parser* parser);
	
};

#endif
