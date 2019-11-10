#include "../header/command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

Command::Command(){}
int* wpidstatus;			//needed for waitpid
int status = 0;
int* statptr = &status;
//int* statusptr = &status;				//store result of execvp failed or suceeded

void Command::runCommand(char ** argv){
	//std::cout << *argv;
	execvp(*argv, argv);		//hijacks child process to retun to parent
		//std::cout << "ok";//*statptr = -1;
	//to do, check for error
}

void Command::runAll(int numOfCommands, Parser* parser){
		for(int i = 0; i < numOfCommands; i++){
			int pid = fork();						//make a child process
			waitpid(pid, wpidstatus, WCONTINUED);		//wait for the child to continue
			if(pid == 0){
				//std::cout << parser->formatArguments(i);
				Command::runCommand(parser->formatArguments(i));
				
			}
		}
}




