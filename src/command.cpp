#include "../header/component.h"
#include "../header/command.h"
#include "../header/test.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
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
	redirect = false;
}

void Command::runCommand(char ** argv){
	Command::err = 0;
//std::cout << "g";
	execvp(*argv, argv);		//hijacks child process to return to parent
	perror("Error");
	//err = errno;
	Command::err = 1;
	std::exit(EXIT_FAILURE);
}

void Command::runAll(int numOfCommands, Component* parser){
	err = 0;
	std::string exit_str = "";
//	std::cout << "numOfCommands: " << numOfCommands << std::endl;

for (int j = 0; j < pattern.size(); j++)
	std::cout << "Pattern: "  << pattern.at(j) << std::endl;

		for(int i = 0; i < numOfCommands; i++){
			exit_str = "";
			
			exit_str = parser->formatArguments(i)[0];	//check if supposed to exit
				if(exit_str == "exit"){
					parser->shouldIExit(true);
					parser->resetVectors();
					std::exit(0);
				}
	
			int pid = fork();						//make a child process	
			if(pid == 0) {
				std::cout << "pid == 0";
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&")	//if && fails
					parser->removeNextCommand(i);
				
				else if(WEXITSTATUS(status) == 0  && parser->pattern.at(i) == "||")	//if || passes
					parser->removeNextCommand(i);

				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&")
					quick_exit(EXIT_FAILURE);

/*	//something is off		
			if (parser->pattern.at(i) == "|" && pid == 0) {
				Piping(to_run.at(i), i, parser); //, to_run.at(i + 1));
				redirect = true;
//				parser->removeNextCommand(i);
			}
			else if (parser->pattern.at(i) == "<" && pid == 0) {
				OverwriteIn(to_run.at(i), i,  parser); //, to_run.at(i + 1));
				redirect = true;
//				parser->removeNextCommand(i);
			}
			
			else if (parser->pattern.at(i) == ">" && pid == 0) {
				OverwriteOutNew(to_run.at(i), i, parser); //, to_run.at(i + 1));
				redirect = true;
//				parser->removeNextCommand(i);
			}
			
			else if (parser->pattern.at(i) == ">>" && pid == 0) {
				OverwriteOut(to_run.at(i), i, parser); //, to_run.at(i + 1));
				redirect = true;
//				parser->removeNextCommand(i);
			}
			
*/		
			char ** arga = parser->formatArguments(i);	

//std::cout << "arga: " << *arga;
			std::string test_str = "test";                          //check if test
				if (*arga == test_str)
					test->Test::runCommand(parser->formatArguments(i));
				
				else {
					this->Command::runCommand(parser->formatArguments(i));
std::cout << "c";
}
			}
			else if (pid < 0) {
				perror("failed fork");
				//return 1;
				std::exit(1);
			}
			else if (pid > 0) {
				if (waitpid(-1, &status, 0) < 0)		//wait for the child to continue
					perror("wait on child");
				if (WIFEXITED(status)) 
					WEXITSTATUS(status);
			}
//	redirect = false;
std::cout << "d";
	}
}

void Command::OverwriteOutNew(std::string to_run_command, int i, Component* parser) {
	int savestdout = dup(1);						//saves stdout in next available loc
	mode_t mode =  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int file_start = to_run_command.find(redirect_out_new_file, 0) + 2;
	std::string fileName =  to_run_command.substr(file_start, (to_run_command.size() - 1));
	int newout = open(fileName.c_str(), O_WRONLY | O_CREAT, mode);

	int command_end = to_run_command.find(redirect_out_new_file, 0) - 2;
	parser->to_run.at(i) = to_run_command.substr(0, command_end);		//gets command to run in execvp

	char** arga = parser->formatArguments(i);
std::cout << "arga: " << *arga;
	std::string test_str = "test";
		if (*arga == test_str)
			test->Test::runCommand(parser->formatArguments(i));
		else
			Command::runCommand(parser->formatArguments(i));

		
	close(1);								//close file to write in
	dup(newout);
	dup2(savestdout, 1);							//puts stdout back to og loc
}

void Command::OverwriteOut(std::string to_run_command, int i, Component* parser) {
	int savestdout = dup(1);						//saves stdout in next available loc
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int file_start = to_run_command.find(redirect_out, 0) + 3;
	std::string fileName = to_run_command.substr(file_start, (to_run_command.size() - 1));
	int newout = open(fileName.c_str(), O_WRONLY | O_CREAT | O_APPEND, mode);          //open file to writ in

	int command_end = to_run_command.find(redirect_out, 0) - 2;
	parser->to_run.at(i) = to_run_command.substr(0, command_end);		//gets command to run in execvp
	
	char** arga = parser->formatArguments(i);
std::cout << "arga: " << *arga;
	std::string test_str = "test";
		if (*arga == test_str)
			test->Test::runCommand(parser->formatArguments(i));
		else 
			Command::runCommand(parser->formatArguments(i));

	close(1);
	dup(newout);
	dup2(savestdout, 1);							//puts stdout back to og loc
}

void Command::OverwriteIn(std::string to_run_command, int i, Component* parser) {
	int savestdin = dup(0);							//saves stdin in next available loc

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int file_start = to_run_command.find(redirect_in, 0) + 2;
	std::string fileName = to_run_command.substr(file_start, (to_run_command.size() - 1));
	int newin = open(fileName.c_str(), O_RDONLY, mode);			//opens a file
std::cout << "e";
	
	int command_end = to_run_command.find(redirect_in, 0) - 2;
	parser->to_run.at(i) = to_run_command.substr(0, command_end);		//gets command to run in execvp

std::cout << "arga: " << *arga;
	char** arga = parser->formatArguments(i); 
	std::string test_str = "test";  		                        //check if test
		if (*arga == test_str)
			test->Test::runCommand(parser->formatArguments(i));
		else
			Command::runCommand(parser->formatArguments(i));

	close(0);
	dup(newin);
	dup2(savestdin, 0);							//puts stdin back to og loc
}

void Command::Piping(std::string to_run_command, int i, Component* parser) {
	
}
/*
void Command::parseNoParens(std::string comm, std::vector<std::string> comms) {
        int pos_start = 0;
        int pos_end = 0;

	while(pos_start < comm.size() && comm.find(space, pos_start) != -1) {
		pos_end = comm.find(space, pos_start);
		if (pos_start < comm.size() && comm.find(quotation_mark, pos_start) != -1) {			//if starts with "
			int temp_pos_start = comm.find(quotation_mark, pos_start);
			if (temp_pos_start <= pos_end) {
				if (comm.at(pos_start) == '\"') {
					pos_start++;
					pos_end = comm.find(quotation_mark, pos_start);
					if (pos_start + (pos_end - pos_start) < comm.size()) {
					comms.push_back(comm.substr(pos_start, (pos_end - pos_start)));
//	std::cout << comms.back() << " = 1 , ";
						pos_end += 2;
						pos_start = pos_end;
					}
				}
			}
			else {
				if (pos_start + (pos_end - pos_start) < comm.size()) {
					comms.push_back(comm.substr(pos_start, (pos_end - pos_start)));
//	std::cout << comms.back() << " = 2 , ";
					pos_end++;
					pos_start = pos_end;
//	std::cout << comms.back() << " = 3 , ";
				pos_end++;
//	std::cout << comms.back() << " = 3 , ";
				pos_end++;
				pos_start = pos_end;
			}
		}
	}
	//assume there is always a last command ofter the last space
	if (pos_start < comm.size()) {
		comms.push_back(comm.substr(pos_start, (comm.size() - pos_start)));
//	std::cout << comms.back() << " = 4 , ";
	}
}
*/
