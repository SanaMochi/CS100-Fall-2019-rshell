#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv){
std::string command;
std::string space = " ";
std::string and_symbol = "&&";
std::string or_symbol = "||";
std::string end_symbol = ";";
std::string path = std::getenv("PATH");
int pos_start = 0;
int pos_end = 0;
std::vector<std::string> commands;
std::vector<std::string> to_run;
//std::cout << "Path: " << path << std::endl;   
std::cout << "$";
std::getline(std::cin, command);

//break up the command string by spaces
while(command.find(space, pos_start) != -1){	
pos_end = command.find(space, pos_start);
//std::cout << "Starting pos: " << pos_start << " Ending pos " << pos_end <<  " Next space: " << command.find(space, pos_start) << std::endl;
commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
pos_end++;
pos_start = pos_end;
}
//assume there is always a last command ofter the last space
commands.push_back(command.substr(pos_start, (command.size() - pos_start)));
/*
for(int i = 0; i < commands.size(); i++){
	std::cout << commands.at(i) << std::endl;
}
*/

//breaks up commands into blocks seperated by '&&' , '||' , ';'
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

for(int i = 0; i < to_run.size(); i++){
	std::cout << to_run.at(i) << std::endl;
}
return 0;
}
