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

void Command::runAll(int numOfCommands, Component* parser){
	err = 0;
	std::string exit_str = "";
	std::cout << "numOfCommands: " << numOfCommands << std::endl;
		for(int i = 0; i < numOfCommands; i++){
			exit_str = "";
			
			exit_str = parser->formatArguments(i)[0];	//check if supposed to exit
				if(exit_str == "exit"){
					parser->shouldIExit(true);
					parser->resetVectors();
					std::exit(0);
				}
	
			int pid = fork();				//make a child process
		//	waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
		
			if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&")	//for &&
				parser->removeNextCommand(i);

			else if(WEXITSTATUS(status) == 0  && parser->pattern.at(i) == "||") //for ||
				parser->removeNextCommand(i);
			
			//std::cout << "\nargs2: "  << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
			if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&")
				quick_exit(EXIT_FAILURE);

			char ** arga = parser->formatArguments(i);	
		//	std::cout << "argv: " << argv.at(0) << std::endl;
			std::cout << "*arga: " << *arga << std::endl;
		//	std::cout << "arga: " << arga << std::endl;

			if(pid == 0) {
				std::string test_str = "test";                          //check if test
        	         //       test_str.c_str();
	
	                        std::cout << "checking test" << std::endl;
	                        if (*arga == test_str) {
	                                std::cout << "running test -- " << std::endl;
	                                test->Test::runCommand(parser->formatArguments(i));
	                        }
	                        else {
	 				std::cout << "running non-test: " << std::endl;
	                                Command::runCommand(parser->formatArguments(i));
	                        }
		/*		std::string test_str.c_str() = "test";
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
		*/
			}else if (pid < 0) {
				perror("failed fork");
				//return 1;
				std::exit(1);
			}else if (pid > 0) {
				if (waitpid(-1, &status, 0) < 0)		//wait for the child to continue
					perror("wait on child");
				if (WIFEXITED(status)) 
					WEXITSTATUS(status);
			}
/*			std::string test_str = "test";				//check if test
			test_str.c_str();
							
			std::cout << "checking test" << std::endl;
			if (*arga == test_str.c_str())	
				std::cout << "running test -- " << std::endl;
				test->Test::runCommand(parser->formatArguments(i));
				}	
			else
				std::cout << "running non-test: " << std::endl;
				Command::runCommand(parser->formatArguments(i));
			}
*
*/
	}
}
