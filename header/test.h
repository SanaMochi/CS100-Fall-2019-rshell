#ifndef _TEST_H_
#define _TEST_H_

#include "component.h"
#include "parser.h"
//#include <string>
//#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
//#include "parser.h"
//#include "component.h"
//#include "command.h"

class Command;
class Test : public Parser {
//	Test();
	std::vector<std::string> flags;
	int isTrue;
	
	int exists(std::string fileName);
	int isRegularFile(std::string fileName);
	int isdirectory(std::string directoryName);
	void runCommand(char ** argv);
	void runAll(int numOfCommands, Component* parser);
};

#endif //_TEST_H_
