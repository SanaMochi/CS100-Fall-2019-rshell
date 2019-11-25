# CS 100 Programming Project

[Link](https://docs.google.com/document/d/1s2KtW2oBfghC4v9x3tm3DPjYiKK5R0QllsNlExJ0rt4/edit) to specs so I dont have to keep on signing into ilearn
compile with `g++ rshell.cpp parser.cpp command.cpp -o main -std=c++11` in src directory

<h1> Project Information </h1>
Fall 2019

* Michael Wdowiak, 862063084, mwdow001@ucr.edu 
* Sana Mohiuddin, 862075288, smohi002@ucr.edu

<h1> Introduction </h1>
We have created a shell in C++ called rshell using a composite pattern to do the following: 

1. Print a command prompt (e.g. `$`)
2. Read in a line of command(s) (and connector(s)) from standard input
3. Parse the input and execute the appropriate commands using `fork` , `execvp` , and `waitpid` 
4. The connector class inherits from and references the command class (making connecto a composite) If the commands are connected by:
    * ";" : execute both
    * "&&" :  execute the next command if the previous one passed
    * "||" : execute the next command if the previous one falied

<h1> Diagram </h1>

![OMT Diagram:](https://github.com/cs100/assignment-michael_sana/blob/master/images/RShell_OMT_Diagram.jpeg)

<h1> Classes </h1>

* Commands - will take in all of the executables and connectors into a vector (using std::cin)

                class Commands {
                  vector <Commands*> comm;
                  void getCommands() {
                    string command;
                    while (cin >> command) {
                      comm.push_back(command);
                    }
                  }
                };
        
* Connector - inherits from Commands; will have subclasses to run each command based on the connector

                class Connector : public Commands {
                  vector <Command*> conn
                  public:
                  void getConnectors() {
                    for (int i = 0; comm.at(i) != " " && comm.at(i) != "\n"; i++) {
                      conn.push_back(comm.at(i));
                    }
                  }
                  virtual void runCommands() {...}
                };

* SemicolonConnector - will run the next command (no matter what)

                class SemicolonConnector : public Connector {
                  public:
                  bool isSemicolon() {
                    //check if semicolon (or not && and not ||)
                  }
                  void runCommand() {
                    //always execute next command
                  }
                };
    
* ANDConnector - will execute the next command if the previous one was successful

                class ADDConnector : public Connector {
                  public:
                  bool isADD() {
                    //check if ADD (or not ; and not ||)
                  }
                  void runCommand() {
                    //execute next command is prev passed
                  }
                };

* ORConnector - will execute if the first one fails

                class ORConnector : public Connector {
                  public:
                  bool isOR() {
                    //check if OR (or not ; and not &&)
                  }
                  void runCommand() {
                    //execute next command is prev failed
                  }
                };

* ExecutableExpression - inherits from Commands; will run the executables

                class ExecutableExpression : public Command {
                  vector <Executable*> commandList;
                  Executable()
                  void parse(const string&) {...}
                  void runExeCommand() {
                    //runs the command
                    //executes next command based on connector
                  }
                }

<h1> Prototypes / Reaserch </h1>

We have created basic prototypes that test and show basic functionality of `fork()` , `execvp()` , `waitpid()`, and parse function.



<h1> Development and Testing Roadmap </h1>

* Create relavant classes that work with the parser (for inputs such as `&&` , `||` , `;`)
* Figure out a parser to use and the functionality of other relevant functions that work with it
* Make unit tests using the `googletest` framework
* Make integration tests using the `googletest` framework
* Add more items as they become necessary
