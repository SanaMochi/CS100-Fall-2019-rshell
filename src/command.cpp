#include "../header/command.h"

Command::Command(){}
virtual runCommand(const char * file, char * const argv[]){
	execvp(file, argv[]);
}
