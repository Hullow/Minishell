#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t childPid;
	printf("Before fork %d\n", getpid());

	// fork creates a child and returns its process ID
	childPid = fork();

	wait(&childPid);

	printf("After fork %d\n", getpid());
	exit(0);
}