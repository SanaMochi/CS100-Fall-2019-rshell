//#include "../header/component.h"
#include "../header/component.h"
#include "../header/command.h"
#include "../header/test.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <iterator>

using namespace std;

Command::Command(){
	status = 0;
	err = 0;
}

void Command::runCommand(char ** argv){
	Command::err = 0;
	
	execvp(*argv, argv);		//hijacks child process to return to parent
	perror("Error");
	//err = errno;
	Command::err = 1;
	std::exit(EXIT_FAILURE);
}

int Command::runAll(int numOfCommands, Component* parser){
	err = 0;	
			char* arga[commands.size() + 1];
			for (int i = 0; i < commands.size() + 1; i++)
				arga[i] = (char*)commands.at(i).c_str();
				
			arga[commands.size() + 1] = NULL;
			
			pid_t pid = fork();				//make a child process
			waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			
			if(pid == 0){

				//std::cout << "\nError: " << err;
				//std::cout << "\nsymbol: " << parser->pattern.at(i);
				//std::cout << "\nargs: " << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				
				if (execvp(arga[0], arga) != 0) {
					perror("exec");
					//return 1;	
					exit(1);
				} else {
					//return 1;
					exit(1);
				}
			}
				
			/*	if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){	//for &&
					parser->removeNextCommand(i);

				}else if(WEXITSTATUS(status) == 0  && parser->pattern.at(i) == "||"){ //for ||
					parser->removeNextCommand(i);
				}
				//std::cout << "\nargs2: "  << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){
					quick_exit(EXIT_FAILURE);
				}
				std::string test_str = "test";
		//		test_str.c_str();
		//						
		//		if (parser->formatArgumants(i)[0] == test_str.c_str())	
		//			test->runCommand(parser->formatArguments(i));
		
				test_str = "";

                       		test_str = parser->formatArguments(i)[0];
                                if(test_.find("test") == -1){
					 test->runCommand(parser->formatArguments(i));
				}	
				else {
					Command::runCommand(parser->formatArguments(i));
				}
		*/	else if (pid < 0) {
				perror("failed fork");
				//return 1;
				exit(1);
			}else if (pid > 0) {
				if (waitpid(-1, &status, 0) < 0)		//wait for the child to continue
					perror("wait on child");
				if (WIFEXITED(status)) {
					return WEXITSTATUS(status);
			}
		//	std::string test_str = "test";
		//		test_str.c_str();
		//						
		//		if (parser->formatArgumants(i)[0] == test_str.c_str())	
		//			if(parser->formatArguments(i)[1] == 
					
				if (commands.at(0) == "test") {
					if (commands.at(1) == "-e") { 
						struct stat buf;
						if (stat(arga[2], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
					else if (commands.at(1) == "-f") { 
						struct stat buf;
						if (stat(arga[2], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
					else if (commands.at(1) == "-d") { 
						struct stat buf;
						if (stat(arga[2], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
					else {
						struct stat buf;
						if (stat(arga[1], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
				}
		
		//		test_str = "";

               //      		test_str = parser->formatArguments(i)[0];
               //               if(test_str.find("test") == -1){
		//			 test->runCommand(parser->formatArguments(i));
				}	
				else {
					std::string exit_str = "";
               				for(int i = 0; i < numOfCommands; i++){
                       				 exit_str = "";

                       				exit_str = parser->formatArguments(i)[0];
                               			if(exit_str == "exit"){
                                        	parser->shouldIExit(true);
                                        	parser->resetVectors();
                                        	std::exit(0);
                                		}	
					Command::runCommand(parser->formatArguments(i));
					}
				}

	return 0;
}
