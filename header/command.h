#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <iostream>
//#include "parser.h"
#include <vector>
#include "component.h"
#include <unistd.h>

class Command : public Component{
	
	public:
	Command();
	virtual runCommand(const char * file, char * const argv[]);
	
};

#endif
