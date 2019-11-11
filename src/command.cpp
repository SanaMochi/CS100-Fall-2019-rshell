#include "../header/command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

Command::Command(){}
int status = 0;
int err = 0;


void Command::runCommand(char ** argv){
	err = 0;

	execvp(*argv, argv);		//hijacks child process to retun to parent
	perror("Error");
	err = errno;
}

void Command::runAll(int numOfCommands, Parser* parser){
	err = 0;
	std::string exit = "";
		for(int i = 0; i < numOfCommands; i++){
			exit = "";
			/*
			exit = parser->formatArguments(i)[0];
				if(exit == "exit"){
					parser->shouldIExit(true);
					parser->resetVectors();
					std::exit(0);
				}*/
			int pid = fork();						//make a child process
			//perror("Error with fork");
			waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			
			if(pid == 0){
				
				if(err != 0 && parser->pattern.at(i) == "&&"){	//for &&
					parser->removeNextCommand(i);
																//for ||
				}else if(err == 0  && parser->pattern.at(i) == "||"){
					parser->removeNextCommand(i);
				}
		
				Command::runCommand(parser->formatArguments(i));
			}
		}
}


