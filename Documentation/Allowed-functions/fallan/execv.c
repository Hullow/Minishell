#include <stdio.h>
#include <unistd.h>

int main(int argc, char const **argv)
{
	printf("Hi there\n");

	// executing an ls command
	char *argv2[] = {"/bin/rmdir", "newdir", NULL};
	execv(argv2[0], argv2);

	printf(".. and done!");
}