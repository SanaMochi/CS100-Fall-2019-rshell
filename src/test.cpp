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
	if (stat(argv[1], &buf) == -1) {	// if no arguments for test
        	perror("stat");
        	//return;
		std::exit(1);
    	}
	else if (argv[1] == "-e") { 		// if file exists
	//	struct stat buf;
		if (S_ISREG(buf.st_mode) != 0) 
        		printf("(True)"); //, file_path) ;
		else if (S_ISDIR(buf.st_mode) != 0)
        		printf("(True)"); //, file_path) ;
    		else
        		printf("(False)"); //, file_path) ;
	//	if (stat(argv[2], &buf) == 0) {
	//		std::cout << "(True)" << std::endl;
			//return 0;
	//		std::exit(0);
	//	}
	//	else {
	//		std::cout << "(False)" << std::endl;
			//return 1;
	//		std::exit(1);
	//	}
	}
	else if (argv[1] == "-f") { 		// if is a regular file
	//	struct stat buf;
		if (S_ISREG(buf.st_mode) != 0) 
        		printf("(True)"); //, file_path) ;
    		else
        		printf("(False)"); //, file_path) ;
	//	if (stat(argv[2], &buf) == 0) {
	//		std::cout << "(True)" << std::endl;
			//return 0;
	//		std::exit(0);
	//	}
	//	else {
	//		std::cout << "(False)" << std::endl;
			//return 1;
	//		std::exit(1);
	//	}
	}
	else if (argv[1] == "-d") {		//if is a directory
	//	struct stat buf;
		if (S_ISDIR(buf.st_mode) != 0)
        		printf("(True)"); //, file_path) ;
    		else
        		printf("(False)"); //, file_path) ;
	//	if (stat(argv[2], &buf) == 0) {
	//		cout << "(True)" << endl;
			//return 0;
	//		std::exit(0);
	//	}
	//	else {
	//		cout << "(False)" << endl;
			//return 1;
	//		std::exit(1);
	//	}
	}
	else {					// default to check if exists
	//	struct stat buf;
		if (S_ISREG(buf.st_mode) != 0) 
        		printf("(True)"); //, file_path) ;
		else if (S_ISDIR(buf.st_mode) != 0)
        		printf("(True)"); //, file_path) ;
    		else
        		printf("(False)"); //, file_path) ;
	//	if (stat(argv[1], &buf) == 0) {
	//		cout << "(True)" << endl;
			//return 0;
	//		std::exit(0);
	//	}
	//	else {
	//		cout << "(False)" << endl;
			//return 1;
	//		std::exit(0);
	//	}
	}
	
	
	/*
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
	*/
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

void Test::runAll(int numOfCommands, Component* parser) {
	if (commands.at(1) == "-e") { 
		struct stat buf;
		if (stat(argv[2], &buf) == 0) {
			std::cout << "(True)" << std::endl;
			return;
		}
		else {
			std::cout << "(False)" << std::endl;
			return;
		}
	}
	else if (commands.at(1) == "-f") { 
		struct stat buf;
		if (stat(argv[2], &buf) == 0) {
			std::cout << "(True)" << std::endl;
			return;
		}
		else {
			std::cout << "(False)" << std::endl;
			return;
		}
	}
	else if (commands.at(1) == "-d") { 
		struct stat buf;
		if (stat(argv[2], &buf) == 0) {
			std::cout << "(True)" << std::endl;
			return;
		}
		else {
			std::cout << "(False)" << std::endl;
			return;
		}
	}
	else {
		struct stat buf;
		if (stat(argv[1], &buf) == 0) {
			std::cout << "(True)" << std::endl;
			return;
		}
		else {
			std::cout << "(False)" << std::endl;
			return;
		}
	}
}

