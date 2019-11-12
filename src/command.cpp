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
	//err = errno;
	err = 1;
	exit(EXIT_FAILURE);
}

void Command::runAll(int numOfCommands, Parser* parser){
	err = 0;
	std::string exit = "";
		for(int i = 0; i < numOfCommands; i++){
			exit = "";
			
			exit = parser->formatArguments(i)[0];
				if(exit == "exit"){
					parser->shouldIExit(true);
					parser->resetVectors();
					std::exit(0);
				}
			int pid = fork();						//make a child process
			//perror("Error with fork");
			waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			
			if(pid == 0){
				//std::cout << "\nError: " << err;
				//std::cout << "\nsymbol: " << parser->pattern.at(i);
				//std::cout << "\nargs: " << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){	//for &&
					parser->removeNextCommand(i);
																//for ||
				}else if(WEXITSTATUS(status) == 0  && parser->pattern.at(i) == "||"){
					parser->removeNextCommand(i);
				}
				//std::cout << "\nargs2: "  << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){
					quick_exit(EXIT_FAILURE);
				}
				Command::runCommand(parser->formatArguments(i));
				
			}
		}
}


