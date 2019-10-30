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

![OMT Diagram:]
(https://raw.github.com/cs100/assignment-michael_sana/master/images/RShell_OMT_Diagram.jpeg?token=AKW57KA6HNI7NO6LOBYDJZC5YJYVY)

<h1> Classes </h1>

* Commands - will take in all of the executables and connectors into a vector.
* Connector - inherits from Commands; will have subclasses to run each command based on the connector
* SemicolonConnector - will run the next command (no matter what)
* ANDConnector - will execute the next command if the previous one was successful
* OrConnector - will execute if the first one fails
* ExecutableExpression - inherits from Commands; will run the executables


<h1> Prototypes / Reaserch </h1>

Insert relavant prototypes that we have made that using `fork()` , `execvp()` , and `waitpid()`, and figure out a parser to use to get input from the console (maybe `std::cin' ?)



<h1> Development and Testing Roadmap </h1>

* Figure out a parser to use
* Create relavant classes that work with the parser (for inputs such as `&&` , `||` , `;`)
* Make integration tests using the `googletest` framework
* Create [Github issues](https://help.github.com/en/github/managing-your-work-on-github/creating-an-issue) for each partner to work on
* Add more items as they become necessary
