#include <iostream>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main (){
	int count = 0;
	pid_t pid = fork();
	int* status;
	
	waitpid(0, status, WCONTINUED);
	//waits for child to go first, then parent
	
	if (pid == 0){	//child
		for (int i = 0; i < 5; i++){
			std::cout << "Child counter: " << count << std::endl;
			count++;
		}
	}else if (pid > 0){	//parent
		for(int i = 0; i < 5; i++){
			std::cout << "Parent counter: " << count << std::endl;
			count++;
		}
	}else{	//failed
		std::cout << "fork failed\n";
		return 1;
	}
	return 0;
}
