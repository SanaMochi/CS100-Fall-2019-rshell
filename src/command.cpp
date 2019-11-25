#include "../header/component.h"
#include "../header/command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

Command::Command(){
	status = 0;
	err = 0;
}

/*
void Command::removeNextCommand(int location){
	if(location > numOfCommands)
		return;
	std::vector<std::string>::iterator loc = fileNames.begin() + location;
	fileNames.erase(loc);
	pattern.erase(loc);
	numOfCommands == fileNames.size();
	int start = 0;
	int end = 0;
	int countQ = 0;
	while(countQ != location){
		for(int i = start; i < argv.size(); i++){
			start++;
			if(argv.at(i) == "???"){
				countQ++;
				break;
			}
			
		}
	}
	//count how many commands are in between that ??? and the next one
	for(int i = start; i < argv.size();i++){
		if(argv.at(i) == "???")
			break;
		end++;
	}
	std::vector<std::string>::iterator v_start, v_end;
	v_start = argv.begin() + start;
	v_end = argv.begin() + start + end + 1;
	argv.erase(v_start, v_end);
}
*/
void Command::runCommand(char ** argv){
	err = 0;

	execvp(*argv, argv);		//hijacks child process to return to parent
	perror("Error");
	//err = errno;
	err = 1;
	std::exit(EXIT_FAILURE);
}

void Command::runAll(int numOfCommands, Component* parser){
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
				Command::runCommand(parser->formatArguments(i));
				
			}else if (pid < 0) {
				quick_exit(EXIT_FAILURE);
			}else if (pid > 0) {
				waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			}
		}
}
