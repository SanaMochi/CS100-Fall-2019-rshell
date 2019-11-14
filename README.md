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

![OMTDiagram:] (https://github.com/cs100/assignment-michael_sana/blob/master/images/RShell_OMT_Diagram.png)
<h1> Classes </h1>

Composite
Inteface class that doesn't do much except hold onto variables needed by inherited classes and some important functions.

Command
Composite class that runs the commands given

Parser
Leaf class that parses the command and executes based on the connector

<h1> Prototypes / Reaserch </h1>

We have created basic prototypes that test and show basic functionality of `fork()` , `execvp()` , `waitpid()`, and parse function.
We have also now created a funtional parse class.

<h1> Development and Testing Roadmap </h1>

* We have created relavant classes that work with the parser (for inputs such as `&&` , `||` , `;`)
* We have figures out a parser to use and the functionality of other relevant functions that work with it
* We made unit and integrationtests using the `googletest` framework
* Add more items as they become necessary such as special cases (parenthesis, etc)
