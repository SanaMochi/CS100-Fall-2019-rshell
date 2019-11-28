#include "../header/parser.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

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

/*	int curr_max = 0; 
    	int max = 0;
 //	std::string temp;
//	temp += "(" + command + ")";
//std::cout << command << std::endl;	
	//find how many pairs of parens
	for (int i = 0; i < command.size(); i++) { 
        	if (command.at(i) == '(') {
            		curr_max++;
			if (curr_max > max) 
               			max = curr_max; 
        	} 
       		else if (command.at(i) == ')') { 
            		if (curr_max > 0)
                	curr_max--; 
		}
//		else {
//                	perror("Error: Uneven parens ");
//			return;
 //       	} 
 	}
    	if (curr_max != 0) {
		perror("Error: Odd parens");
		return;
	}
	//max is how many pairs of parens 
	if (max == 0) {
		*/
		while(command.find(space, pos_start) != -1) {		
			if (command.find(quotation_mark, pos_start) != -1) {			//if starts with quotation mark
				pos_end = command.find(quotation_mark, pos_start + 1);
			}
			else {
				pos_end = command.find(space, pos_start);
			}

			if (pos_start + (pos_end - pos_start) < command.size()) {
				commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
			
			pos_end++;
			pos_start = pos_end;
			}
		}
		//assume there is always a last command ofter the last space
		commands.push_back(command.substr(pos_start, (command.size() - pos_start)));
//	}
/*	else if (max > 0) {
		std::string command_og = command;
		if (command.at(0) != '(') {
			
			std::string temp;
			temp += "(" + command + ")";
			command = temp;
	//		std::cout << command << std::endl;
		}	
		for (int n = 0; n < command.size(); n++) { //while(command.find(opening_parens, pos_start) != -1) {
			if (command.at(n) == '(') {
				std::cout << " open" << n << std::endl;
				opened_parens.push_back(n);
//				std::cout << opened_parens.at(0) << std::endl;
			}
			else if (command.at(n) == ')') {
				std::cout << " closed" << n << std::endl;
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
				std::cout << "blah" << std::endl;
				std::cout << opened_parens.back();
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
		std::cout << " start " << pos_start << " end " << pos_end << std::endl;
					int end_paren_num = 0;
//					int temp_end = pos_end;
					if (command.at(pos_end - 1) == ')') {	//bc end == ' '
//						end_paren_num++;
						pos_end--;
						std::cout << " end " << pos_end << std::endl;
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
				std::cout << "c";
						pos_end += 2;
				std::cout << "d";

						if (opened_parens.size() > 0)
							opened_parens.erase(opened_parens.begin() + o);
		std::cout << "open_parens: " << opened_parens.size() << std::endl;
		std::cout << "e";
					}else 
						pos_end++;
				std::cout << "f";
					if (pos_end != command.size())
						pos_start = pos_end;
				std::cout << " start/end " << pos_start << " " << pos_end << std::endl;
					if ((pos_start == command.size() - 1) && (command_og.at(0) !=  '('))
						pos_start = k;
					std::cout << "g"; 
					if (pos_start == k)
						isk = true;

			std::cout << "a"; 
				}
				std::cout << "b";

			int paren_count = 0;
			std::string temporary = command;
			while (command.at(temporary.size() - 1) == ')') {
				paren_count++;
				temporary.pop_back();
			}

			commands.push_back(command.substr(pos_start, (command.size() - paren_count - pos_start)));
			std::cout << " command_substr: " << commands.back() << std::endl;

		std::cout << "b";
//		if (opened_parens.size() > 0)
//			opened_parens.erase(opened_parens.begin() + o);

		}
	}
	*/
	
	for (int i = 0; i < commands.size(); i++){
		//std::cout << "comparing: " << commands.at(i) << " and &&\n";
		if(commands.at(i) == and_symbol)
			pattern.push_back(and_symbol);

		else if(commands.at(i) == or_symbol)
			pattern.push_back(or_symbol);
		else if(commands.at(i) == end_symbol)
			pattern.push_back(end_symbol);
//start
		else if (commands.at(i) == open_bracket)
			pattern.push_back(open_bracket);
		else if (commands.at(i) == closed_bracket)
			pattern.push_back(closed_bracket);
//end
	}
	
	for(int i = 0; i < commands.size(); i++){
		std::string temp_str = "";
		
		while(i < commands.size() && commands.at(i) != and_symbol && commands.at(i) != or_symbol && commands.at(i) != end_symbol){
//start
			if (commands.at(i) == open_bracket) {
				commands.at(i) = "test";
				while (commands.at(i) != closed_bracket) {
					temp_str += commands.at(i);
//					if (commands.at(i).back() == ')')
//						commands.at(i).pop_back();
					temp_str += " ";
					i++;
				}
				commands.erase(commands.begin() + 1);
			}
//end
			else {
				temp_str += commands.at(i);

//				if (commands.at(i).back() == ')')
//					commands.at(i).pop_back();
				temp_str += " ";
				i++;
//				std::cout << temp_str << std::endl;
			}
		}
			to_run.push_back(temp_str);
	std::cout << "Command: " << temp_str << std::endl;
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
	argv.push_back(NULL);
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

int Parser::getSize(){
	return fileNames.size();
}

void Parser::runCommand(char ** argv){
	err = 0;

	execvp(*argv, argv);		//hijacks child process to return to parent
	perror("Error");
	err = errno;
}


int Parser::runAll(int numOfCommands, Component* parser){
return 0;

//Command::runAll(numOfCommands, parser);

/*	err = 0;	
			char* arga[commands.size() + 1];
			for (int i = 0; i < commands.size() + 1; i++)
				arga[i] = (char*)commands.at(i).c_str();
				
			arga[commands.size() + 1] = NULL;
			
			pid_t pid = fork();				//make a child process

			waitpid(pid, &status, WCONTINUED);		//wait for the child to continue
			
			if(pid == 0){

				//std::cout << "\nError: " << err;
				//std::cout << "\nsymbol: " << parser->pattern.at(i);
				//std::cout << "\nargs: " << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				
				if (execvp(arga[0], arga) != 0) {
					perror("exec");
					//return 1;	
					exit(1)
				} else {
					//return 1;
					exit(1)
				}
			}
				
			/*	if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){	//for &&
					parser->removeNextCommand(i);
				}else if(WEXITSTATUS(status) == 0  && parser->pattern.at(i) == "||"){ //for ||
					parser->removeNextCommand(i);
				}
				//std::cout << "\nargs2: "  << getpid() << " status: " << WEXITSTATUS(status);parser->printArguments();
				if(WEXITSTATUS(status) == 1 && parser->pattern.at(i) == "&&"){
					quick_exit(EXIT_FAILURE);
				}
				std::string test_str = "test";
		//		test_str.c_str();
		//						
		//		if (parser->formatArgumants(i)[0] == test_str.c_str())	
		//			test->runCommand(parser->formatArguments(i));
	
				test_str = "";
                       		test_str = parser->formatArguments(i)[0];
                                if(test_.find("test") == -1){
					 test->runCommand(parser->formatArguments(i));
				}	
				else {
					Command::runCommand(parser->formatArguments(i));
				}
			else if (pid < 0) {
				perror("failed fork");
				//return 1;
				exit(1)
			}else if (pid > 0) {
				if (waitpid(-1, &status, 0) < 0)		//wait for the child to continue
					perror("wait on child");
				if (WIFEXITED(status)) {
					return WEXITSTATUS(status);
			}
		//	std::string test_str = "test";
		//		test_str.c_str();
		//						
		//		if (parser->formatArgumants(i)[0] == test_str.c_str())	
		//			if(parser->formatArguments(i)[1] == 
					
				if (commands.at(0) == "test") {
					if (commands.at(1) == "-e") { 
						struct stat buf;
						if (stat(arga[2], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
					else if (commands.at(1) == "-f") { 
						struct stat buf;
						if (stat(arga[2], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
					else if (commands.at(1) == "-d") { 
						struct stat buf;
						if (stat(arga[2], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
					else {
						struct stat buf;
						if (stat(arga[1], &buf) == 0) {
							cout << "(True)" << endl;
							return 0;
						}
						else {
							cout << "(False)" << endl;
							return 1;
						}
					}
				}
		
		//		test_str = "";

               //      		test_str = parser->formatArguments(i)[0];
               //               if(test_str.find("test") == -1){
		//			 test->runCommand(parser->formatArguments(i));
				}	
				else {
					std::string exit_str = "";
               				for(int i = 0; i < numOfCommands; i++){
                       				 exit_str = "";

                       				exit_str = parser->formatArguments(i)[0];
                               			if(exit_str == "exit"){
                                        	parser->shouldIExit(true);
                                        	parser->resetVectors();
                                        	std::exit(0);
                                		}	
					Command::runCommand(parser->formatArguments(i));
					}
				}
		}
	return 0;
*/

}
void Parser::deletePointer(){
	for(int i = 0; i < pointerSize; i++)
		delete[] pointer[i];
	delete[] pointer;
}
