#include <pty.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cstdlib>

// Creting my own matrix framework instead of working with the SFML for just testing nothing else

int main(){
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	std::cout << "This goes into the file!\n";
	return 0;
}