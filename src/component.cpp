#include "../header/component.h"
#include <string>

std::string Component::getPattern(int i) {
	if (i > pattern.size()) {
		throw "out of range";
	}
	return pattern.at(i);
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
int Component::getSize(){return fileNames.size();}
