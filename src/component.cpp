#include "../header/component.h"
#include <string>

Component::~Component() {
//	for (int i = 0; i < pointerSize; i++) {
//		delete[] pointer[i];
//	}
//	delete[] pointer;
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
	//		std::cout << "argv: " << argv.at(i) << std::endl;
			if(argv.at(i) == "???"){
				countQ++;
				break;
			}
			
		}
	}
	//count how many commands are in between that ??? and the next one
	for(int i = index; i < argv.size();i++){
	//	 std::cout << "argv: " << argv.at(i) << std::endl;
		if(argv.at(i) == "???")
			break;
		commandCount++;
	}
	pointerSize = commandCount;		//argv.size();
	pointerSize += 2;		// for some reason execvp ignores the first argument and there needs to be room for a null char at the end
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

void Component::resetVectors(){
	pattern.erase(pattern.begin(), pattern.end());
	commands.erase(commands.begin(), commands.end());
	to_run.erase(to_run.begin(), to_run.end());
	fileNames.erase(fileNames.begin(), fileNames.end());
	argv.erase(argv.begin(), argv.end());
	numOfCommands = 0;
	//deletePointer();
}

bool Component::shouldIExit(){
	return exit_bool;
}

void Component::shouldIExit(bool shouldI){
	exit_bool = shouldI;
}
bool Component::getTestBool() {
	return this->test_bool;
}
void Component::setTestTrue() {
	this->test_bool = true;
}
void Component::setTestFalse() {
	this->test_bool = false;
}
void Component::to_run_pop_front() {
	to_run.erase(to_run.begin(), to_run.begin() + 1);
}
