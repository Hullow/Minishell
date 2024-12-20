#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int beeps = 0;

void handler (int sig)
{
	printf("BEEP\n");

	(void)sig;
	if (++beeps < 2)
		alarm(1);
	else if (++beeps < 5)
		execve(NULL, NULL, NULL); // execve resets signals to default, including ignore
	else
	{
		printf("DING DING!\n");
		exit(0);
	}
}

int main()
{
	signal(SIGALRM, handler);
	alarm(3);

	while (1)
	{
	}
}