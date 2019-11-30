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
*/

void Test::runCommand(char ** argv) {
	struct stat buf;
	if (stat(argv[1], &buf) == -1) {	// if no arguments for test
        	perror("stat");
		std::exit(1);
    	}
	else if (stat(argv[1], &buf) == 0) {
		stat(argv[1], &buf);
		if (S_ISREG(buf.st_mode) != 0) 
			printf("(True)"); //, file_path) ;
		else if (S_ISDIR(buf.st_mode) != 0)
			printf("(True)"); //, file_path) ;
		else
			printf("(False)"); //, file_path) ;
	}
	else if (stat(argv[2], &buf) == 0) {
		if (argv[1] == "-e") { 		// if file exists
		//	struct stat buf;
			stat(argv[2], &buf);
			if (S_ISREG(buf.st_mode) != 0) {
				std::cout << "(True)" << std::endl;
			if (S_ISDIR(buf.st_mode) != 0)
				std::cout << "(True)" << std::endl;
			else
				std::cout << "(False)" << std::endl;
		}
		else if (argv[1] == "-f") { 		// if is a regular file
		//	struct stat buf;
			stat(argv[2], &buf);
			if (S_ISREG(buf.st_mode) != 0) 
				std::cout << "(True)" << std::endl;
			else
				std::cout << "(False)" << std::endl;

		}
		else if (argv[1] == "-d") {		//if is a directory
		//	struct stat buf;
			stat(argv[2], &buf);
			if (S_ISDIR(buf.st_mode) != 0)
				std::cout << "(True)" << std::endl;
			else
				std::cout << "(False)" << std::endl;
		}
	}
}
void Test::runAll(int numOfCommands, Component* parser) {
	struct stat buf;
	if (stat(argv[1], &buf) == -1) {	// if no arguments for test
        	perror("stat");
		std::exit(1);
    	}
	else if (stat(argv[1], &buf) == 0) {
		stat(argv[1], &buf);
		if (S_ISREG(buf.st_mode) != 0) 
			printf("(True)"); //, file_path) ;
		else if (S_ISDIR(buf.st_mode) != 0)
			printf("(True)"); //, file_path) ;
		else
			printf("(False)"); //, file_path) ;
	}
	else if (stat(argv[2], &buf) == 0) {
		if (argv[1] == "-e") { 		// if file exists
		//	struct stat buf;
			stat(argv[2], &buf);
			if (S_ISREG(buf.st_mode) != 0) {
				std::cout << "(True)" << std::endl;
			if (S_ISDIR(buf.st_mode) != 0)
				std::cout << "(True)" << std::endl;
			else
				std::cout << "(False)" << std::endl;
		}
		else if (argv[1] == "-f") { 		// if is a regular file
		//	struct stat buf;
			stat(argv[2], &buf);
			if (S_ISREG(buf.st_mode) != 0) 
				std::cout << "(True)" << std::endl;
			else
				std::cout << "(False)" << std::endl;

		}
		else if (argv[1] == "-d") {		//if is a directory
		//	struct stat buf;
			stat(argv[2], &buf);
			if (S_ISDIR(buf.st_mode) != 0)
				std::cout << "(True)" << std::endl;
			else
				std::cout << "(False)" << std::endl;
		}
	}
}

