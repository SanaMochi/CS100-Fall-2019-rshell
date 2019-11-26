#include "../header/component.h"
#include "../header/test.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void Test::runCommand(char ** argv) {
int i = 0;
	while (argv[i] != NULL) {
		status = system(argv[i]);
		if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)) {
			break;
		}
//	status = -1;
	i++;
	}
}

void Test::runAll(int numOfCommands, Component* parser) {
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
			int pid = fork();				//make a child process
			waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			
			if(pid == 0){

				//std::cout << "\nError: " << err;
				//std::cout << "\nsymbol: " << parser->pattern.at(i);
				//std::cout << "\nargs: " << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){	//for &&
					parser->removeNextCommand(i);

				}else if(WEXITSTATUS(status) == 0  && parser->pattern.at(i) == "||"){ //for ||
					parser->removeNextCommand(i);
				}
				//std::cout << "\nargs2: "  << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){
					quick_exit(EXIT_FAILURE);
				}
				Test::runCommand(parser->formatArguments(i));
				
			}else if (pid < 0) {
				quick_exit(EXIT_FAILURE);
			}else if (pid > 0) {
				waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			}
		}
}
