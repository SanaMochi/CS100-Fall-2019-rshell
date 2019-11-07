#include "../header/command.h"

Command::Command(){}


void Command::runCommand(const char * file, char ** argv){
	execvp(file, argv);
}

void Command::runAll(std::vector<std::string> file_names, std::vector<std::string> arguments){
	//TO-DO
}


