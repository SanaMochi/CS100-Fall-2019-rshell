#include "../header/command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

int status = 0;
int err = 0;
Component *c;
Command::Command(){}

void Command::runCommand(char ** argv){
	err = 0;

	execvp(*argv, argv);		//hijacks child process to retun to parent
	perror("Error");
	//err = errno;
	err = 1;
	exit(EXIT_FAILURE);
}
// echo hello > file.txt

void Command::outputRedirection(std::string str){\
	//int out_backup = dup(1);
	int pos = str.find(">");
	std::string f_name = str.substr(pos + 2, -1);
	f_name.erase(f_name.size()-1, -1);
	std::cout << "\nFile name: " << f_name << "/";
	//f_name = "file.txt";
	int fd = open(f_name.c_str(), O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
	int start = str.find(" ");
	pos = str.find(">");
	str = str.substr(start+1, pos - start - 2);
	const char * buf = str.c_str();
	//std::cout << "\nout: " << out_backup << "\nfd: " << fd;
	write(fd, str.c_str(), str.size());
	//dup2(1, fd);
	//std::cout << std::endl << str << std::endl;
	//dup2(out_backup, 1);
	close(fd);
}
void Command::outputRedirectionAppend(std::string str){\
	//int out_backup = dup(1);
	int pos = str.find(">>") +1;
	std::string f_name = str.substr(pos + 2, -1);
	f_name.erase(f_name.size()-1, -1);
	std::cout << "\nFile name: " << f_name << "/";
	//f_name = "file.txt";
	int fd = open(f_name.c_str(), O_RDWR|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR);
	int start = str.find(" ");
	pos = str.find(">>");
	str = str.substr(start+1, pos - start - 2);
	std::cout << "\nstr " << str;
	const char * buf = str.c_str();
	//std::cout << "\nout: " << out_backup << "\nfd: " << fd;
	write(fd, str.c_str(), str.size());
	//dup2(1, fd);
	//std::cout << std::endl << str << std::endl;
	//dup2(out_backup, 1);
	close(fd);
}

void Command::inputRedirection(std::string str){
	int input_backup = dup(0);
	int pos = str.find("<") + 1;
}

void Command::pipe(std::string str){
	//to do

}

int Command::countArgs(char ** argv){
	int i = 0;
	while(argv[i] != nullptr){
		//std::cout << "\nArgv: " << argv[i];
		i++;
	}
	return i;
}
int Command::getLenght(char ** argv, int i){
	int length = 0;
	while(argv[i][length] != '<')
		length++;
	return length;
}

void Command::runAll(int numOfCommands, Parser* parser){
	//Command::outputRedirection(parser->to_run.at(0));

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
			int pid = fork();						//make a child process
			//perror("Error with fork");
			waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			
			if(pid == 0){
				//std::cout << "\nError: " << err;
				//std::cout << "\nsymbol: " << parser->pattern.at(i);
				//std::cout << "\nargs: " << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){	//for &&
					parser->removeNextCommand(i);
																//for ||
				}else if(WEXITSTATUS(status) == 0  && parser->pattern.at(i) == "||"){
					parser->removeNextCommand(i);
				}
				//std::cout << "\nargs2: "  << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){
					quick_exit(EXIT_FAILURE);
				}
				std::string arg;
				int number = Command::countArgs(parser->formatArguments(i));
				for(int x = 0; x < number; x++)
				arg += parser->formatArguments(i)[x];
				if(arg.find(">>") != -1){
					Command::outputRedirectionAppend(parser->to_run.at(i));
				}if(arg.find("|") != -1){
					Command::pipe(parser->to_run.at(i));
				}else if(arg.find("<") != -1){
					Command::inputRedirection(parser->to_run.at(i));
				}else if(arg.find(">") != -1){
					//std::cout << "\nyes <\n";
					Command::outputRedirection(parser->to_run.at(i));
				}else{
					//std::cout << "\nno <\n";
					Command::runCommand(parser->formatArguments(i));
				}
				quick_exit(EXIT_SUCCESS);
			}
		}
}


