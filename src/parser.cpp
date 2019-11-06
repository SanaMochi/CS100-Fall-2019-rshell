#include "../header/parser.h"

Parser::Parser(){ command = "";}
Parser::Parser(std::string s){ command = s; }

void Parser::getInput(std::string s){ command = s; }

void Parser::print(){
	std::cout << command << std::endl;
}

std::vector<std::string> Parser::parse(){
	int pos_start = 0;
	int pos_end = 0;
	//std::cout << "Input : " << command << " " << command.find("t", 0) << " <--" << std::endl;
	while(command.find(space, pos_start) != -1){	
		pos_end = command.find(space, pos_start);
		//std::cout << "Starting pos: " << pos_start << " Ending pos " << pos_end <<  " Next space: " << command.find(space, pos_start) << std::endl;
		commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
		pos_end++;
		pos_start = pos_end;
	}
	//assume there is always a last command ofter the last space
	commands.push_back(command.substr(pos_start, (command.size() - pos_start)));
	//std::cout << commands.size() << std::endl;
	
	for(int i = 0; i < commands.size(); i++){
	std::string temp_str = "";
	while(commands.size() != (i) && commands.at(i) != and_symbol && commands.at(i) != or_symbol && commands.at(i) != end_symbol){
		temp_str += commands.at(i);
		temp_str += " ";
		i++;
		//std::cout <<temp_str << std::endl;
	}
	to_run.push_back(temp_str);
	//std::cout << to_run.at(x) << std::endl;
	}
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
		std::cout << to_run.at(i) << " ,";
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
		std::cout << fileNames.at(i) << " , ";
	}
}
//--------------------fix this-------------------------
//parses the arguments for each file, followed by a ??? to signify that these arguments are for the next file
void Parser::parseArguments(){
	int pos_start = 0;
	int pos_end = 0;
	pos_start = to_run.at(0).find(" ", pos_start);
	for(int x = 0; x < to_run.size(); x++){
		while(to_run.at(x).find(space, pos_start) != -1){	
		pos_end = to_run.at(x).find(space, pos_start);
		//std::cout << "Starting pos: " << pos_start << " Ending pos " << pos_end <<  " Next space: " << command.find(space, pos_start) << std::endl;
		argv.push_back(to_run.at(x).substr(pos_start, (pos_end - pos_start)));
		pos_end++;
		pos_start = pos_end;
	}
	//assume there is always a last command ofter the last space
	argv.push_back(to_run.at(x).substr(pos_start, (to_run.at(x).size() - pos_start)));
	argv.push_back("???");
	}
}

void Parser::printArguments(){
	std::cout << std::endl << "Size: " << argv.size() << std::endl;
	for(int i = 0; i < argv.size(); i++){
		std::cout << argv.at(i) << " , ";
	}
	std::cout << std::endl;
}


























