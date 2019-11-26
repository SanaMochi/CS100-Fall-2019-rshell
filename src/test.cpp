#include "../header/component.h"
#include "../header/test.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void runCommand(char ** argv) {
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

void runAll(int numOfCommands, Component* parser) {

}
