#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "parser.h"

class Component{
	
//	Component* nextCommand;
//	char** command;				//moved to command class so composite pattern (idk how much it changes things, I'll see if it works
	
	public:
	virtual void runCommand(char ** argv) = 0;
	virtual void runAll(int numOfCommands, Parser* parser) = 0;
};
#endif
