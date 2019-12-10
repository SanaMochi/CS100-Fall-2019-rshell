#ifndef _TEST_H_
#define _TEST_H_

#include "component.h"
#include "parser.h"
//#include <string>
//#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
//#include "parser.h"
//#include "component.h"
//#include "command.h"

class Command;
class Test : public Parser {
	public:
	void runCommand(char ** argv);
	void runAll(int numOfCommands, Component* parser);
};

#endif //_TEST_H_
