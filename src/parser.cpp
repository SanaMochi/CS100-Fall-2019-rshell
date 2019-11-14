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
	while(command.find(space, pos_start) != -1){	
		pos_end = command.find(space, pos_start);
		commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
		pos_end++;
		pos_start = pos_end;
		
		
	}
	//assume there is always a last command ofter the last space
	commands.push_back(command.substr(pos_start, (command.size() - pos_start)));
	
	for(int i = 0; i < commands.size(); i++){
		//std::cout << "\ncomparing: " << commands.at(i) << " and &&";
		if(commands.at(i) == and_symbol)
			pattern.push_back(and_symbol);
		else if(commands.at(i) == or_symbol)
			pattern.push_back(or_symbol);
		else if(commands.at(i) == end_symbol)
			pattern.push_back(end_symbol);
	}
	
	for(int i = 0; i < commands.size(); i++){
	std::string temp_str = "";
	
		
	while(commands.size() != (i) && commands.at(i) != and_symbol && commands.at(i) != or_symbol && commands.at(i) != end_symbol){
		temp_str += commands.at(i);
		temp_str += " ";
		i++;
	}
	to_run.push_back(temp_str);
	}
	Parser::parseFileNames();
	Parser::parseArguments();
	numOfCommands = fileNames.size();
	//pattern.push_back("");
}

void Parser::printCommands(){
	if(commands.empty())
		std::cout << "No commads" << std::endl;
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

/*
char** Parser::formatArguments(int location){
	if(location >= argv.size() || location >= fileNames.size())
		return NULL;
	int index = 0;
	int countQ = 0;
	int commandCount = 0;
	while(countQ != location){
		for(int i = index; i < argv.size(); i++){
			index++;
			if(argv.at(i) == "???"){
				countQ++;
				break;
			}
			
		}
	}
	//count how many commands are in between that ??? and the next one
	for(int i = index; i < argv.size();i++){
		if(argv.at(i) == "???")
			break;
		commandCount++;
	}
	pointerSize = commandCount;//argv.size();
	pointerSize += 2;		// for some reson execvp ignores the first argument and there needs to be room for a null char at the end
	char** c = new char *[pointerSize];
	int num = 0;
	c[num] = const_cast<char*> (fileNames.at(location).c_str());	//make the first argument the name of the file, get ignored by ececvp
	num++;
	for(int i = index; commandCount > 0; i++){
		commandCount--;
		c[num] = const_cast<char*> (argv.at(i).c_str()); 
		num++;
	}
	c[num] = NULL;
	pointer = c;
	return c;
}

void Parser::resetVectors(){
	pattern.erase(pattern.begin(), pattern.end());
	commands.erase(commands.begin(), commands.end());
	to_run.erase(to_run.begin(), to_run.end());
	fileNames.erase(fileNames.begin(), fileNames.end());
	argv.erase(argv.begin(), argv.end());
	numOfCommands = 0;
	//deletePointer();
}
*/
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
void Parser::removeNextCommand(int location){
	if(location > numOfCommands)
		return;
	std::vector<std::string>::iterator loc = fileNames.begin() + location;
	fileNames.erase(loc);
	pattern.erase(loc);
	numOfCommands == fileNames.size();
	int start = 0;
	int end = 0;
	int countQ = 0;
	while(countQ != location){
		for(int i = start; i < argv.size(); i++){
			start++;
			if(argv.at(i) == "???"){
				countQ++;
				break;
			}
			
		}
	}
	//count how many commands are in between that ??? and the next one
	for(int i = start; i < argv.size();i++){
		if(argv.at(i) == "???")
			break;
		end++;
	}
	std::vector<std::string>::iterator v_start, v_end;
	v_start = argv.begin() + start;
	v_end = argv.begin() + start + end + 1;
	argv.erase(v_start, v_end);
}

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
/*
	err = 0;
	std::string exit = "";
		for(int i = 0; i < numOfCommands; i++){
			exit = "";

/*			exit = parser->formatArguments(i)[0];
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
																//for ||
				}else if(err == 0  && parser->pattern.at(i) == "||"){
					parser->removeNextCommand(i);
				}
		
				Command::runCommand(parser->formatArguments(i));
			}
		}

*/		
}

void Parser::deletePointer(){
	for(int i = 0; i < pointerSize; i++)
		delete[] pointer[i];
	delete[] pointer;
}



























