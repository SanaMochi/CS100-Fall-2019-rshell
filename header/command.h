#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <iostream>
#include "parser.h"
#include <vector>
#include "component.h"
#include <unistd.h>

class Command : public Component{
	Parser p;
	public:
	Command();
	virtual void runCommand(char ** argv);
	
	virtual void runAll(int numOfCommands, Parser* parser);

	
};

#endif
