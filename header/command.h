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
	virtual void runCommand(const char * file, char ** argv);
	
	virtual void runAll(std::vector<std::string> file_names, std::vector<std::string> arguments);

	
};

#endif
