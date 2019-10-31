# CS 100 Programming Project

<h1> Project Information </h1>
Fall 2019

* Michael Wdowiak, 862063084, mwdow001@ucr.edu 
* Sana Mohiuddin, 862075288, smohi002@ucr.edu

<h1> Introduction </h1>
We have created a shell in C++ called rshell, which is able to do the following: 

1. Print a command prompt (e.g. `$`)
2. Read in a line of command(s) (and connector(s)) from standard input
3. Execute the appropriate commands using `fork` , `execvp` , and `waitpid` 

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

We have created basic prototypes that test and show basic functionality of 'fork()' , 'waitpid()', and 'execvp'



<h1> Development and Testing Roadmap </h1>

* Figure out a parser to use
* Create relavant classes that work with the parser (for inputs such as `&&` , `||` , `;`)
* Make integration tests using the `googletest` framework
* Create [Github issues](https://help.github.com/en/github/managing-your-work-on-github/creating-an-issue) for each partner to work on
* Add more items as they become necessary
