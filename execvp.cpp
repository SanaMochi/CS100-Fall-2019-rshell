#include <iostream>
#include <unistd.h>

int main(){
	//opens geany
	char *args[]={"/bin/geany",NULL}; 
    execvp(args[0],args); 
        
	return 0;
}
