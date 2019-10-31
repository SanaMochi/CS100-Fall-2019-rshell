#include <iostream>
#include <vector>
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>

using namespace std;

class Command {};

class Executable : public Command {
  vector<string> comm;
  
  public:
    void getCommandLine(int argc, char ** argv) {
      // use argc, argv instead of cin
      // string temp;
      // while (cin >> temp) {
      //   comm.push_back(temp);
      // }
      for (int i = 0; i < argc; i++) {
        comm.push_back(argv[i]);
        //figure out how to push+back Command*
      }
    }
    void parser(char ** argv) {
      pid_t child;
      int childStat;
      if (child == 0) {
        //use execvp (if returns = failed)
        if (execvp(*argv, argv) < 0) {
               printf("Error\n");
               exit(1);
          }
      }
      else {
        do {
          //use waitpid() to wait so parent can wait on child
        } while(wait(&childStat) != child);
      }
    }
};
int main(int argc, char ** argv) {

  return 0;
}