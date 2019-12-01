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
			
			std::string temp;
			temp += "(" + command + ")";
			command = temp;
	//		std::cout << command << std::endl;
//		}
		stack<int> s;
		for (int i = 0; i < command.size(); i++) {
			if (command.at(i) == '(')
				s.push(i);
			else if (command.at(i) == ')') {
				int start = s.pop();
				for (int j = start; j < i - start; j++) {
					Parser::parseNoParens(command.substr(start, i - start));	
				command.erase(start, i - start);
			}
		}
		for (int n = 0; n < command.size(); n++) { //while(command.find(opening_parens, pos_start) != -1) {
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
			int k = opened_parens.back();
			int o = opened_parens.size() - 1;
//			int k = opened_parens.at(opened_parens.size() - 1 - j);
//			pos_start = k;
			for (int j = 0; j < closed_parens.size(); j++) {
//				int k = opened_parens.at(opened_parens.size() - 1 - j);
//				int o = opened_parens.size() - 1;
//				std::cout << "blah" << std::endl;
//				std::cout << opened_parens.back();
//          	int o = opened_parens.size() - 1;

				std::cout << " Size & at(open): " << opened_parens.size() << " " << k;
				pos_start = opened_parens.back();
				while (closed_parens.at(j) < opened_parens.at(o) && o > 0) {
					o--;
					pos_start = opened_parens.at(o);
				}
				bool isk = false;
			while(command.find(space, pos_start) != -1 && isk == false && command.at(pos_end) != command.at(closed_parens.at(j))) { // || opened_parens.size() != 0) {	
					while (command.at(pos_start) == '(') { 
						pos_start++;	
					}
					if ((command.find(quotation_mark, pos_start) != -1)) {			//if starts with quotation mark
						pos_end = command.find(quotation_mark, pos_start + 1);
					}
					else {
						pos_end = command.find(space, pos_start);
					}
//		std::cout << " start " << pos_start << " end " << pos_end << std::endl;
					int end_paren_num = 0;
//					int temp_end = pos_end;
					if (command.at(pos_end - 1) == ')') {	//bc end == ' '
//						end_paren_num++;
						pos_end--;
//						std::cout << " end " << pos_end << std::endl;
					}
//					pos_end -=  end_paren_num;
	//	std::cout << " end " << pos_end;
				if (pos_start + (pos_end - pos_start) < command.size())
						commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
		std::cout << " command_substr: " << commands.back() << std::endl;
	//				}
		std::cout << " start " << pos_start << " end " << pos_end << std::endl;
		std::cout << " command: " << command << std::endl;
					if (command.at(pos_end + end_paren_num) == ')') {		//pos_end < (command.size() - end_paren_num - 1) && 
//				std::cout << "c";
						pos_end += 2;
//				std::cout << "d";

						if (opened_parens.size() > 0)
							opened_parens.erase(opened_parens.begin() + o);
//		std::cout << "open_parens: " << opened_parens.size() << std::endl;
//		std::cout << "e";
					}else 
						pos_end++;
//				std::cout << "f";
					if (pos_end != command.size())
						pos_start = pos_end;
//				std::cout << " start/end " << pos_start << " " << pos_end << std::endl;
					if ((pos_start == command.size() - 1) && (command_og.at(0) !=  '('))
						pos_start = k;
//					std::cout << "g"; 
					if (pos_start == k)
						isk = true;

//			std::cout << "a"; 
				}
//				std::cout << "b";

			int paren_count = 0;
			std::string temporary = command;
			while (command.at(temporary.size() - 1) == ')') {
				paren_count++;
				temporary.pop_back();
			}

			commands.push_back(command.substr(pos_start, (command.size() - paren_count - pos_start)));
//			std::cout << " command_substr: " << commands.back() << std::endl;

//		std::cout << "b";
//		if (opened_parens.size() > 0)
//			opened_parens.erase(opened_parens.begin() + o);

		}
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

	}
	
	for(int i = 0; i < commands.size(); i++){
		std::string temp_str = "";
		
		while(i < commands.size() && commands.at(i) != and_symbol && commands.at(i) != or_symbol && commands.at(i) != end_symbol){
			if (commands.at(i) == open_bracket) {
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
//				std::cout << temp_str << std::endl;
			}
		}
			to_run.push_back(temp_str);
//	std::cout << "Command: " << temp_str << std::endl;
	}
	Parser::parseFileNames();
	Parser::parseArguments();
	numOfCommands = fileNames.size();
	//pattern.push_back("");
}

void Parser::parseNoParens(std::string comm) {
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
						pos_end += 2;
						pos_start = pos_end;
					}
				}
			}
			else {
				if (pos_start + (pos_end - pos_start) < comm.size())
					commands.push_back(comm.substr(pos_start, (pos_end - pos_start)));
					pos_end++;
					pos_start = pos_end;
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
		for(int i = 0; i < commands.size(); i++){
			std::cout << commands.at(i) << " , ";
		}
		std::cout << std::endl;
	}
	for(int i = 0; i < to_run.size(); i++){
		std::cout << to_run.at(i) << " , ";
	}
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
