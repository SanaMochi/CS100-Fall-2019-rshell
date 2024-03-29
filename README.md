# CS 100 Programming Project

<h1> Project Information </h1>
Fall 2019

* Michael Wdowiak, 862063084, mwdow001@ucr.edu 
* Sana Mohiuddin, 862075288, smohi002@ucr.edu

<h1> Introduction </h1>
We have created a shell in C++ called rshell using a composite pattern to do the following: 

1. Print a command prompt (e.g. `$`)
2. Read in a line of command(s) (and connector(s)) from standard input
3. Parse the input and execute the appropriate commands using `fork` , `execvp` , and `waitpid`
    * If `test`, use `stat()` instead and print (Ture) or (False)
4. The connector class inherits from and references the command class (making connecto a composite) If the commands are connected by:
    * ";" : execute both
    * "&&" :  execute the next command if the previous one passed
    * "||" : execute the next command if the previous one falied
5. Also no redirects input and output
    * "<" : redirects input from stdin to a file
    * ">" : redirects stdout to a new file (creates the file first and then outputs it there & overwrites if already exists)
    * ">>" : redirects stdout to a file (if doesn't exist - create a new file; if exists - adds on to file)
    * "|" : passes the output of one command as input to another

<h1> Diagram </h1>

![OMTDiagram: ](https://github.com/cs100/assignment-michael_sana/blob/master/images/RShell_OMT_Diagram.jpeg)
<h1> Classes </h1>

Composite:
Inteface class that doesn't do much except hold onto variables needed by inherited classes and some important functions.

Command:
Composite class that runs the commands given using  `execvp()`
the runCommand function also has an added functionality to call Test class when `test` is invoked.
   
      int pid = fork();				                                       //make a child process
			char ** arga = parser->formatArguments(i);	
			if(pid == 0) {
				std::string test_str = "test";                              //check if test
	            if (*arga == test_str)                       //if test
	               test->Test::runCommand(parser->formatArguments(i));
	            else                                         //if not test
	               Command::runCommand(parser->formatArguments(i));
         }
Also uses `dup()` and `dup2()` to redirect `stdout` and `stdin`.
	
	void Command::OverwriteOutNew(std::string to_run_command, int i, Component* parser) {
		int savestdout = dup(1);						//saves stdout in next available loc
		mode_t mode =  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
		int file_start = to_run_command.find(redirect_out_new_file, 0) + 2;
		std::string fileName =  to_run_command.substr(file_start, (to_run_command.size() - 1));
		int newout = open(fileName.c_str(), O_WRONLY | O_CREAT, mode);

		int command_end = to_run_command.find(redirect_out_new_file, 0) - 2;
		parser->to_run.at(i) = to_run_command.substr(0, command_end);		//gets command to run in execvp

		char** arga = parser->formatArguments(i);
		std::string test_str = "test";
			if (*arga == test_str)
				test->Test::runCommand(parser->formatArguments(i));
			else
				Command::runCommand(parser->formatArguments(i));


		close(1);								//close file to write in
		dup(newout);
		dup2(savestdout, 1);							//puts stdout back to og loc
	}

	
Parser:
Leaf class that parses the command and executes based on the connector
If surrounded by quotes, arguments are treated as a single argument, no matter what they contain.
Parentheses can be used in order to change the order of precedence of operators in the rshell. Includes multiple and nested parenthesis.

		while(pos_start < command.size() && command.find(space, pos_start) != -1) {      //simplified for no '\"' or '('
			pos_end = command.find(space, pos_start);
			if (pos_start + (pos_end - pos_start) < command.size())
           	commands.push_back(command.substr(pos_start, (pos_end - pos_start)));
						pos_end++;
                  pos_start = pos_end;
   		}
		}
		//assume there is always a last command ofter the last space
		if (pos_start < command.size()) {
			commands.push_back(command.substr(pos_start, (command.size() - pos_start)));
		}

Test:
Runs test through the `test` operator and square brackets, `[ ]`. This is done using `stat()` to check the specifics of a file based on  the privided flag. 
    * "-e" : file exists (`ISREG()` or `ISDIR()`) - used as default if no flag is provided
    * "-f" : file is a regular file (`ISREG()`)
    * "-d" : file is a directory (`ISDIR()`)

            if (stat(argv[1], &buf) != -1) { //if no flag
               stat(argv[1], &buf);
               if (S_ISREG(buf.st_mode) != 0)
                  std::cout << "(True)" << std::endl;
               else if (S_ISDIR(buf.st_mode) != 0)
                  std::cout << "(True)" << std::endl;
            }

<h1> Prototypes / Reaserch </h1>

We have created basic prototypes that test and show basic functionality of `fork()` , `execvp()` , `waitpid()`, and parse function.
We have also now created a funtional parse class.

<h1> Development and Testing Roadmap </h1>

* We have created relavant classes that work with the parser (for inputs such as `&&` , `||` , `;`)
* We have figures out a parser to use and the functionality of other relevant functions that work with it
* We made unit and integration tests using the `googletest` framework
* Add more items as they become necessary such as special cases (parenthesis, etc)
