#include "../header/parser.h"

Parser::Parser(){ command = "";}
Parser::Parser(std::string s){ command = s; }

void Parser::getInput(std::string s){ command = s; }

void Parser::print(){
	std::cout << command << std::endl;
}

void Parser::parse(){
	int pos_start = 0;
	int pos_end = 0;
	resetVectors();
	Parser::preParse();
	while(command.find(space, pos_start) != -1){	
		pos_end = command.find(space, pos_start);
		commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
		pos_end++;
		pos_start = pos_end;
	}
	//assume there is always a last command ofter the last space
	commands.push_back(command.substr(pos_start, (command.size() - pos_start)));
	
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


const char* Parser::formatFileName(int location){
	return fileNames.at(location).c_str();
}

char** Parser::formatArguments(int location){
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
	c[num+1] = NULL;
	pointer = c;
	return c;
}

int Parser::getSize(){return fileNames.size();}

void Parser::resetVectors(){
	commands.erase(commands.begin(), commands.end());
	to_run.erase(to_run.begin(), to_run.end());
	fileNames.erase(fileNames.begin(), fileNames.end());
	argv.erase(argv.begin(), argv.end());
}

void Parser::preParse(){
											//look for comments
	int commentLocation = command.find("#");
	if(commentLocation != -1){
		command.erase(commentLocation, (command.size() - commentLocation));
	}
											//trim and unwanted spaces
	command.erase(command.find_last_not_of(" ")+1);
	std::cout << std::endl << command << std::endl;
}
//--------------------fix this--------------------
void Parser::deletePointer(){
	for(int i = 0; i < pointerSize; i++)
		delete[] pointer[i];
	delete[] pointer;
}




























