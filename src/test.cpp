#include "../header/component.h"
#include "../header/parser.h"
#include "../header/test.h"
#include <stdlib.h>

void Test::runCommand(char ** argv) {
	struct stat buf;
	if (stat(argv[1], &buf) != -1) {
		stat(argv[1], &buf);
		if (S_ISREG(buf.st_mode) != 0) {
			std::cout << "(True)" << std::endl;
			Component::setTestTrue();
		}
		else if (S_ISDIR(buf.st_mode) != 0) {
			std::cout << "(True)" << std::endl;
			Component::setTestTrue();
		}
	}
	else if (stat(argv[2], &buf) != -1) {
		if (std::string(argv[1]) == "-e") { 			// if file exists
			stat(argv[2], &buf);
			if (S_ISREG(buf.st_mode) != 0) {
				std::cout << "(True)" << std::endl;
				Component::setTestTrue();
			}
			else if (S_ISDIR(buf.st_mode) != 0) {
				std::cout << "(True)" << std::endl;
				Component::setTestTrue();
			}
		}
		else if (std::string(argv[1]) == "-f") { 		// if is a regular file
			stat(argv[2], &buf);
			if (S_ISREG(buf.st_mode) != 0) {
				std::cout << "(True)" << std::endl;
				Component::setTestTrue();
			}
		}
		else if (std::string(argv[1]) == "-d") {		//if is a directory
			stat(argv[2], &buf);
			if (S_ISDIR(buf.st_mode) != 0) {
				std::cout << "(True)" << std::endl;
				Component::setTestTrue();
			}
		}
		else {
			if (stat(argv[1], &buf) == -1) {        // if no arguments for test
				perror("stat");
				std::exit(1);
			}
		}
	}
	else {
		std::cout << "(False)" << std::endl;
		Component::setTestFalse();
	}
}
void Test::runAll(int numOfCommands, Component* parser) {}
