#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "component.h"

class Command : public Component{
	protected:
	char** command;
	Component* nextCommand;			//makes this class a composite
	int status;
	int err;
	
	public:
	Command();
//	void removeNextCommand(int location);
	
	virtual void runCommand(char ** argv);
	
	virtual void runAll(int numOfCommands, Component* parser);
	//void makeList(int numOfCommands, Parser* parser);
	
};

#endif
