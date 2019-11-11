#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class Component{
	
	Component* nextCommand;
	char** command;
	
	public:
	virtual void runCommand(char ** argv) = 0;
	virtual void runAll(int numOfCommands, Parser* parser) = 0;
};
#endif
