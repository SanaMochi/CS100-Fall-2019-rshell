#include "../header/command.h"
#include <unistd.h>
#include <sys/wait.h>

Command::Command(){}
int* status;

void Command::runCommand(char ** argv){
	execvp(*argv, argv);					//hijacks child process to retun to parent		
}

void Command::runAll(int numOfCommands, Parser* parser){
	
		for(int i = 0; i < numOfCommands; i++){
			
			int pid = fork();						//make a child process
			waitpid(pid, status, WCONTINUED);		//wait for the child to continue
			if(pid == 0)
				Command::runCommand(parser->formatArguments(i));
		}
}


