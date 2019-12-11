#include "../header/parser.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stack>

using namespace std;

Parser::Parser(){
	command = "";
	status = 0;
	err = 0;
	numOfCommands = 0;
	exit_bool = false;
	opened_parens.resize(0);
	closed_parens.resize(0);
}
Parser::Parser(std::string s){
	command = s;
	status = 0;
	err = 0;
	exit_bool = false;
	opened_parens.resize(0);
        closed_parens.resize(0);

}

void Parser::getInput(std::string s){ command = s; }

void Parser::print(){
	std::cout << command << std::endl;
}

void Parser::parse(){
	int pos_start = 0;
	int pos_end = 0;
	resetVectors();
 	Parser::preParse();
	pattern.push_back("");

	int curr_max = 0; 
    	int numParens = 0;

	//find how many pairs of parens
	for (int i = 0; i < command.size(); i++) { 
        	if (command.at(i) == '(') {
            		curr_max++;
			if (curr_max > numParens) 
               			numParens = curr_max; 
        	} 
       		else if (command.at(i) == ')') { 
            		if (curr_max > 0)
                	curr_max--; 
		}
 	}
    	if (curr_max != 0) {
		perror("Error: Odd parens");
		return;
	}
	if (numParens == 0)
		Parser::parseNoParens(command);
	else if (numParens > 0) {
		std::string command_og = command;
//		if (command.at(0) != '(') {
			
//			std::string temp;
//			temp += "(" + command + ")";
//			command = temp;
	//		std::cout << command << std::endl;
//		}
		stack<int> s;
		for (int i = 0; i < command.size(); i++) {
			if (command.at(i) == '(') {
				s.push(i);
				opened_parens.push_back(i);
			}
			else if (command.at(i) == ')') {
				int start = s.top();
				closed_parens.push_back(i);
				s.pop();
				int end = i - start;
				int temp1 = 0;
				int temp2 = 0;
				while (command.at(start + temp1) == ' ' || command.at(start + temp1) == '(')
					temp1++;
				while (command.at(start + end - temp2) == ' ' || command.at(start + end - temp2) == ')')
					temp2++; 
				Parser::parseNoParens(command.substr(start + temp1, end - temp2));	
//	std::cout << "to be parsed: " << command.substr(start + temp1, end - temp2) << std::endl;

				to_run_parens.push_back(command.substr(start + temp1, end - temp2));
				command.erase(start, end);
//	std::cout << "leftover: " << command << std::endl;
					if (start < command.size())
						i = start;
					else if (command.size() != 0)
						i = 0;
			}
			if (i >= command.size() && i != 0)
				i = 0;
		}
//for (int i = 0; i < commands.size(); i++) {
//	std::cout << commands.at(i) << ", ";
//}
//std::cout << std::endl;

/*		for (int n = 0; n < command.size(); n++) { //while(command.find(opening_parens, pos_start) != -1) {
			if (command.at(n) == '(') {
//				std::cout << " open" << n << std::endl;
				opened_parens.push_back(n);
//				std::cout << opened_parens.at(0) << std::endl;
			}
			else if (command.at(n) == ')') {
//				std::cout << " closed" << n << std::endl;
			    	closed_parens.push_back(n);
			}
		}
*/      //                temp += "(" + command_og + ")";
        //                command = temp;

//			int k = opened_parens.back();
//			int o = opened_parens.size() - 1;
	}

	
	for (int i = 0; i < commands.size(); i++){
		//std::cout << "comparing: " << commands.at(i) << " and &&\n";
		if(commands.at(i) == and_symbol)
			pattern.push_back(and_symbol);

		else if(commands.at(i) == or_symbol)
			pattern.push_back(or_symbol);
		else if(commands.at(i) == end_symbol)
			pattern.push_back(end_symbol);

		else if (commands.at(i) == open_bracket)
			pattern.push_back(open_bracket);
		else if (commands.at(i) == closed_bracket)
			pattern.push_back(closed_bracket);
		
		else if (commands.at(i) == pipe_symbol)
			pattern.push_back(pipe_symbol);
		else if (commands.at(i) == redirect_in)
			pattern.push_back(redirect_in);
		else if (commands.at(i) == redirect_out_new_file)
			pattern.push_back(redirect_out_new_file);
		else if (commands.at(i) == redirect_out)
			pattern.push_back(redirect_out);

	}
	
	for(int i = 0; i < commands.size(); i++){
		std::string temp_str = "";
		
		while(i < commands.size() && commands.at(i) != and_symbol && commands.at(i) != or_symbol && commands.at(i) != end_symbol) { // && commands.at(i) != pipe_symbol && commands.at(i) != redirect_in && commands.at(i) != redirect_out_new_file && commands.at(i) != redirect_out){
			if (commands.at(i) == open_bracket) {			//if symbolic test
				commands.at(i) = "test";
				while (commands.at(i) != closed_bracket) {
					temp_str += commands.at(i);
					if (commands.at(i).back() == ')')
						commands.at(i).pop_back();
					temp_str += " ";
					i++;
				}
				commands.erase(commands.begin() + 1);
			}
			else {
				temp_str += commands.at(i);

				if (commands.at(i).back() == ')')
					commands.at(i).pop_back();
				temp_str += " ";
				i++;
			}
		}
			to_run.push_back(temp_str);
//	std::cout << "Command: " << temp_str << std::endl;
	}
//std::cout << "pattern: "; printPattern();
	Parser::parseFileNames();
//		std:: cout << "files: "; printFileNames();
	Parser::parseArguments();
	numOfCommands = fileNames.size();
}

void Parser::parseNoParens(std::string comm) {
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
					commands.push_back(comm.substr(pos_start, (pos_end - pos_start)));
//	std::cout << commands.back() << " = 1 , ";
						pos_end += 2;
						pos_start = pos_end;
					}
				}
			}
			else {
				if (pos_start + (pos_end - pos_start) < comm.size()) {
					commands.push_back(comm.substr(pos_start, (pos_end - pos_start)));
//	std::cout << commands.back() << " = 2 , ";
					pos_end++;
					pos_start = pos_end;
				}
			}
		}	
		else {
			 if (pos_start + (pos_end - pos_start) < comm.size()) {
				commands.push_back(comm.substr(pos_start, (pos_end - pos_start)));
				pos_end++;
				pos_start = pos_end;
			}
		}
	}
	//assume there is always a last command ofter the last space
	if (pos_start < comm.size()) {
		commands.push_back(comm.substr(pos_start, (comm.size() - pos_start)));
	}
}
	
void Parser::printCommands(){
	if(commands.empty())
		std::cout << "No commands" << std::endl;
	else{
		for(int i = 0; i < commands.size(); i++)
			std::cout << commands.at(i) << " , ";
		std::cout << std::endl;
	}
	for(int i = 0; i < to_run.size(); i++)
		std::cout << to_run.at(i) << " , ";
	std::cout << std::endl;
}

std::vector<std::string> Parser::getCommandsToRun(){
	return to_run;
}

//gets the file names only
void Parser::parseFileNames(){
	int pos_start = 0;
	int pos_end = 0;
	for(int i = 0; i < to_run.size(); i++){
		pos_end = to_run.at(i).find(" ", pos_start);
//		if (to_run.at(i).substr(pos_start, pos_end) != ">" || to_run.at(i).substr(pos_start, pos_end) != "<" || to_run.at(i).substr(pos_start, pos_end) != ">>" || to_run.at(i).substr(pos_start, pos_end) != "|")
			fileNames.push_back(to_run.at(i).substr(pos_start, pos_end));
	}
}

//parses the arguments for each file, followed by a ??? to signify that these arguments are for the next file
void Parser::parseArguments(){
	for(int x = 0; x < to_run.size(); x++){
		int pos_start = 0;
		int pos_end = 0;
		pos_start = to_run.at(x).find(" ", pos_start) + 1;		//ignore the firsr word (its the file name)
		while(to_run.at(x).find(space, pos_start) != -1){	
			pos_end = to_run.at(x).find(space, pos_start);
//			if (to_run.at(x).substr(pos_start, (pos_end - pos_start)) != ">" || to_run.at(x).substr(pos_start, (pos_end - pos_start)) != "<" || to_run.at(x).substr(pos_start, (pos_end - pos_start)) != ">>" || to_run.at(x).substr(pos_start, (pos_end - pos_start)) != "|")
				argv.push_back(to_run.at(x).substr(pos_start, (pos_end - pos_start)));
			pos_end++;
			pos_start = pos_end;
	}
	//assume there is always a last command ofter the last space
	argv.push_back("???");
	}
}

void Parser::printArguments(){
	for(int i = 0; i < argv.size(); i++){
		std::cout << argv.at(i) << " , ";
	}
	std::cout << std::endl;
}

void Parser::printFileNames(){
	for(int i = 0; i < fileNames.size(); i++){
		std::cout << fileNames.at(i) << " , ";
	}
	std::cout << std::endl;
}

void Parser::printPattern(){
	for(int i = 0; i < pattern.size(); i++){
		std::cout << pattern.at(i) << " , ";
	}
	std::cout << std::endl;
}

const char* Parser::formatFileName(int location){
	return fileNames.at(location).c_str();
}

void Parser::preParse(){
	int commentLocation = command.find("#");
	if(commentLocation != -1){
		command.erase(commentLocation, (command.size() - commentLocation));
	}
											//trim and unwanted spaces
	command.erase(command.find_last_not_of(" ")+1);
	
	//std::cout << std::endl << command << std::endl;
}

int Parser::getSize(){
	return fileNames.size();
}

void Parser::runCommand(char ** argv) {}

void Parser::runAll(int numOfCommands, Component* parser) {}

void Parser::deletePointer() {}
