#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class Component{
	Parser p;
	
	public:
	virtual void runCommand(const char * file, char ** argv) = 0;
	virtual void runAll(std::vector<std::string> file_names, std::vector<std::string> arguments) = 0;
};
#endif
