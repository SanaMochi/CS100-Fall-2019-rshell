#ifndef _TEST_H_
#define _TEST_H_

#include <string>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "component.h"
#include "command.h"

class Test : public Component {
	void runCommand(char ** argv);
	void runAll(int numOfCommands, Component* parser);
};

#endif //_TEST_H_
