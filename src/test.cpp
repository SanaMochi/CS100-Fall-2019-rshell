#include "../header/component.h"
#include "../header/parser.h"
#include "../header/test.h"
#include <stdlib.h>
//#include <stdio.h>

/*Test::Test() {
	command = "";
        err = 0;
        status = 0;
        numOfCommands = 0;
        exit = false;
}
Test::Test(std::string s) {
	command = s;
	err = 0;
	status = 0;
	numOfCommands = 0;
	exit = false;
}
/*
int exists(std::string fileName) {
	if (isRegularFile(fileName) == 0 || isDirectory(fileName) == 0) {
		return 0;
	}
	return 1;
}

int isRegularFile(std::string fileName) {
	FILE* file;
	file = fopen(fileName);
	if (file == NULL) {
		return 1;
	}
	return 0;
}

int isDirectory(std::string directoryName) {
	DIR* dir;
	dir = opendir(directoryName);
	if (dir == NULL) {
		return 1;
	}
	return 0;
}
*/
void Test::runCommand(char ** argv) {
	struct stat buf;

	if (stat(argv[1], &buf) == -1) {
        	perror("stat");
        	return;
    	}
	if (stat(argv[1], &buf) != -1) { // Check the return value of stat
    		if (S_ISREG(buf.st_mode) != 0) 
        		printf("(True)"); //, file_path) ;
		else if (S_ISDIR(buf.st_mode) != 0)
        		printf("(True)"); //, file_path) ;
    	}
    	else {
        	printf("(False)"); //, file_path) ;
    	}
	
}
/*int i = 0;
	//assuming ONLY test executables
	if (argv[i] != NULL) {
//		status = system(argv[i]);
	
//		if (WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)) {
//			break;
//		}
		i++;
		if (argv[i] == "-e" || argv[i] == "-f" || argv[i] == "-d") {
			flags.push_back(argv[i];
			i++;
		}
		else if (flags.size() == 0)
			flags.push_back("-e");
//		for (int j = 0; j < flags.size(); j++) {
			if (flag.at(j) == "-e") {
				isTrue = exists(argv[i]);
			}else if (flag.at(j) == "-f") {
				isTrue = isRegularFile(argv[i]);
			}else if (flag.at(j) == "-d") {
				isTrue = isDirectory(argv[i]);
			}
			if (isTrue == 0) {
				std::cout << "(True)" << std::endl;
			}else {
				std::cout << "(False)" << std::endl;
//		}
//	i++;
	}
}
*/
/*
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
*/
