#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// how to fix exit.c for "exit <numerical value>"
// 
int main(int argc, char **argv)
{
	pid_t		exit_arg;
	int			exit_status;

	if (argc != 2)
		return 0;
	exit_arg = atoi(argv[1]);
	if (exit_arg == -1 && strcmp(argv[1], "-1")) // if we have something else than -1 as input resulting in exit_arg -1
	{
		printf("Minishell: exit: %s: numeric argument required\n", argv[1]);
		exit_status = 255;
	}
	else if (exit_status >= 0)
		exit_status = exit_arg % 256;
	else
		exit_status = 256 + (exit_arg % 256);
	printf("exit_arg: %d\n", exit_arg);
	printf("exit_status: %d\n", exit_status);
	return (0);
}
