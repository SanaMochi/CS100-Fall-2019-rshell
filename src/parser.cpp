#include "../header/parser.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

Parser::Parser(){
	command = "";
	status = 0;
	err = 0;
	numOfCommands = 0;
	exit = false;
}
Parser::Parser(std::string s){
	command = s;
	status = 0;
	err = 0;
	exit = false;
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
    	int max = 0;
 	
    for (int i = 0; i < command.size(); i++) { 
        if (command.at(i) == '(') {
            curr_max++;
		if (curr_max > max) 
                max = curr_max; 
        } 
        else if (command.at(i) == ')') { 
            if (curr_max > 0)
                curr_max--; 
            else {
                perror("Error: ");
		return;
	    }
        } 
    }
  
    	if (current_max != 0) {
		perror("Error: ");
		return;
	}
	}//max is how many nested parens 
	
	while(command.find(space, pos_start) != -1){			
		if (command.find(quotation_mark, pos_start) != -1) {			//if starts with quotation mark
		//	if (command.find(quotation_mark, pos_start + 1 == -1)) {
				//error not even number of parens
			pos_end = command.find(quotation_mark, pos_start + 1);
		}
		else {
			pos_end = command.find(space, pos_start);
		}
		
		if (pos_start + (pos_end - pos_start) < command.size()) {
			commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
		}
		pos_end++;
		pos_start = pos_end;
		
		
	}
	//assume there is always a last command ofter the last space
//	if (command.find(space, pos_start) == 1) {
//		commands.push_back(command.substr(pos_start, (command.size() - 1 - pos_start)));
//	}
//	if (pos_start + (command.size() - pos_start) < command.size())
	commands.push_back(command.substr(pos_start, (command.size() - pos_start)));
	
	for(int i = 0; i < commands.size(); i++){
		//std::cout << "\ncomparing: " << commands.at(i) << " and &&";
		if(commands.at(i) == and_symbol)
			pattern.push_back(and_symbol);

		else if(commands.at(i) == or_symbol)
			pattern.push_back(or_symbol);
		else if(commands.at(i) == end_symbol)
			pattern.push_back(end_symbol);
//start
//		else if (commands.at(i) == "test")
//			pattern.push_back("test");
		else if (commands.at(i) == open_bracket)
			pattern.push_back(open_bracket);
		else if (commands.at(i) == closed_bracket)
			pattern.push_back(closed_bracket);
//end
	}
	
	//find parenthesese first and save it into to_run
/*	int index_pos_start = 0;
	for (int i = 0; i < commands.size(); i++) {
		std::string temp_str = "";
	std::cout << "Commands.size()1: " << commands.size() << std::endl;	
		if (commands.at(i).find(opening_parens, 0) != -1) {
			pos_start = commands.at(i).find(opening_parens, 0) + 1;
			temp_str = commands.at(i).substr(pos_start, commands.at(i).size() - 1);
	std::cout << "i: " << i << std::endl;
			to_run.push_back(temp_str);
			commands.erase(commands.begin() + i);
//			std::cout << temp_str << std::endl;
//need to implement for pattern and if quotes and parens
//getting vector out of range  error when run with parens
			while (commands.at(i).find(closing_parens, 0) == -1 && i < commands.size()) {
//				std::cout << temp_str << std::endl;
				temp_str = commands.at(i);
				to_run.push_back(temp_str);
				commands.erase(commands.begin() + i);
			}
		}
		
		if (commands.at(i).find(closing_parens, 0) != -1) { 
			pos_end = commands.at(i).find(closing_parens, 0);
			temp_str = commands.at(i).substr(0 , pos_end);
	std::cout << "Commands.size()2: " << commands.size() << "\n i: " << i << std::endl;
			to_run.push_back(temp_str);
			commands.erase(commands.begin() + i);
		}
//		std::cout << temp_str << std::endl;
		
	}
*/
	for(int i = 0; i < commands.size(); i++){
		std::string temp_str = "";
		
		while(i < commands.size() && commands.at(i) != and_symbol && commands.at(i) != or_symbol && commands.at(i) != end_symbol){
//start
			if (commands.at(i) == open_bracket) {
//				temp_str += "test ";
				commands.at(i) = "test";
				while (commands.at(i) != closed_bracket) {
					temp_str += commands.at(i);
					temp_str += " ";
					i++;
				}
				commands.erase(commands.begin() + 1);
			}
//end
			else {
				temp_str += commands.at(i);
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
	//std::cout << "\nShould delete \" at: " << command.find_first_of("\"") << " and " << command.find_last_of("\"") << std::endl;
	//std::cout << "\nOld String: " << command;
	//command.erase(command.find_first_of("\""));			//Fix this
	//command.erase(command.find_last_of("\""));
	//std::cout << "\nNew String: " << command;
												//look for comments
	int commentLocation = command.find("#");
	if(commentLocation != -1){
		command.erase(commentLocation, (command.size() - commentLocation));
	}
											//trim and unwanted spaces
	command.erase(command.find_last_not_of(" ")+1);
	
	//std::cout << std::endl << command << std::endl;
}

/*
bool Parser::shouldIExit(){
	return exit;
}
void Parser::shouldIExit(bool shouldI){
	exit = shouldI;
}
*/

int Parser::getSize(){
	return fileNames.size();
}

void Parser::runCommand(char ** argv){
	err = 0;

	execvp(*argv, argv);		//hijacks child process to return to parent
	perror("Error");
	err = errno;
}


void Parser::runAll(int numOfCommands, Component* parser){
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
				
				if(err != 0 && parser->pattern.at(i) == "&&"){	//for &&
					parser->removeNextCommand(i);

				}else if(err == 0  && parser->pattern.at(i) == "||"){ //for ||
					parser->removeNextCommand(i);
				}
//start				
//				else if (parser.pattern.at(i) == "test")
//					parser->Test::runCommand();
				else if (parser->pattern.at(i) == "[")
					parser->removeNextCommand(i);
//					parser->test::runCommand();
				else if (parser->pattern.at(i) == "]") 
					parser->removeNextCommand(i);
		
//end
				Parser::runCommand(parser->formatArguments(i));
			}
		}

	
}

void Parser::deletePointer(){
	for(int i = 0; i < pointerSize; i++)
		delete[] pointer[i];
	delete[] pointer;
}
