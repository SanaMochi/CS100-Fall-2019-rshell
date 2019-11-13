#include "../header/component.h"
#include <string>

std::string Component::getPattern(int i) {
	if (i > pattern.size()) {
		throw "out of range";
	}
	return pattern.at(i);
}
/*
void Component::printArguments(){
	for(int i = 0; i < argv.size(); i++){
		std::cout << argv.at(i) << " , ";
	}
	std::cout << std::endl;
}

void Component::printFileNames(){
	for(int i = 0; i < fileNames.size(); i++){
		std::cout << fileNames.at(i) << " , ";
	}
	std::cout << std::endl;
}

void Component::printPattern(){
	for(int i = 0; i < pattern.size(); i++){
		std::cout << pattern.at(i) << " , ";
	}
	std::cout << std::endl;
}
const char* Component::formatFileName(int location){
	return fileNames.at(location).c_str();
}

char** Component::formatArguments(int location){
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

int Component::getSize(){return fileNames.size();}

void Component::resetVectors(){
	pattern.erase(pattern.begin(), pattern.end());
	commands.erase(commands.begin(), commands.end());
	to_run.erase(to_run.begin(), to_run.end());
	fileNames.erase(fileNames.begin(), fileNames.end());
	argv.erase(argv.begin(), argv.end());
	numOfCommands = 0;
	//deletePointer();
}

void Component::preParse(){
	//command.erase(command.find_first_of("\""));			Fix this
	//command.erase(command.find_last_of("\""));
											//look for comments
	int commentLocation = command.find("#");
	if(commentLocation != -1){
		command.erase(commentLocation, (command.size() - commentLocation));
	}
											//trim and unwanted spaces
	command.erase(command.find_last_not_of(" ")+1);
	
	//std::cout << std::endl << command << std::endl;
}

void Component::removeNextCommand(int location){
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

bool Component::shouldIExit(){
	return exit;
}

void Component::shouldIExit(bool shouldI){
	exit = shouldI;
}
*/
