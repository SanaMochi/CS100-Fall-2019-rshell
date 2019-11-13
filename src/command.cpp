#include "../header/component.h"
#include "../header/command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

Command::Command(){
	status = 0;
	err = 0;
}

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

void Command::runCommand(char ** argv){
	err = 0;

	execvp(*argv, argv);		//hijacks child process to return to parent
	perror("Error");
	err = errno;
}

void Command::runAll(int numOfCommands, Component* parser){
	err = 0;
	std::string exit = "";
		for(int i = 0; i < numOfCommands; i++){
			exit = "";
			int pid = fork();						//make a child process
			waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			
			if(pid == 0){
				
				if(err != 0 && parser->getPattern(i) == "&&"){	//for &&
					parser->removeNextCommand(i);
																//for ||
				}else if(err == 0  && parser->getPattern(i) == "||"){
					parser->removeNextCommand(i);
				}
		
				Command::runCommand(parser->formatArguments(i));
			}
		}
}


