/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10minshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:57:03 by francis           #+#    #+#             */
/*   Updated: 2024/06/27 17:32:41 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// From YouTube tutorial [EnthusiastiCon - Stefanie Schirmer “OMG building a shell in 10 minutes”](https://www.youtube.com/watch?v=k6TTj4C0LF0)
// Nb: incomplete, missing functions => doesn't run

#include <stdio.h> // printf
#include <string.h> // strlen
#include <stdlib.h> // exit
#include <unistd.h> // syscalls

int MAXLINE = 1024;
char prompt[] = "10msh> "; // command line prompt

// maxargds in struct can't be variable, use define
#define MAXARGS 128

struct command {
	int argc;				// number of args
	char *argv[MAXARGS];	// arguments list
	enum builtin_t {		// is argv[0] a builtin command ?
		NONE, QUIT, JOBS, BG, FG } builtin;
};

void runSystemCommand(struct command *cmd, int bg);
int parse(const char *cmdline, struct command *cmd);
void eval(char *cmdline);

void runSystemCommand(struct command *cmd, int bg) {
	pid_t childPid;
	if ((childPid = fork()) < 0)
		error("fork() error");
	else if (childPid == 0) { // I'm the child and could run a command
		// EXECVP !!!
		if (execvp(cmd->argv[0], cmd->argv) < 0) {
			printf("%s: Command not found\n", cmd->argv[0]);
			exit(0);
		}
	}
	else { // I'm the parent. Shell continues here.
		if (bg)
			printf("Child in background [%d]\n", childPid);
		else
			wait(&childPid);
	}
}

int parse(const char *cmdline, struct command *cmd) {
	static char array[MAXLINE];			// local copy of command line
	const char delims[10] = " \t\r\n";	// argument delimiters
	char *line = array;					// ptr that traverses command line
	char *token;						// ptr to the end of the current arg
	char *endline;						// ptr to the end of the cmdline string
	int  is_bg;							// background job ?

	if (cmdline == NULL)
		error("command line is NULL\n");

	(void) strncpy(line, cmdline, MAXLINE);
	endline = line + strlen(line);

	// build argv list
	cmd->argc = 0;

	while (line < endline) {
		// skip delimiters
		line += strspn (line, delims);
		if (line >= endline) break;

		// Find token delimiter
		token = line + strcspn (line, delims);

		// terminate the token
		*token = '\0';

		// Record token as argument
		cmd->argv[cmd->argc++] = line;

		// Check if argv is full
		if (cmd->argc >= MAXARGS - 1) break;

		line = token + 1;
	}

	// argument list must end with a NULL pointer
	cmd->argv[cmd->argc] = NULL;

	if (cmd->argc == 0) // ignore blank line
		return 1;
	
	cmd->builtin = parseBuiltin(cmd);

	// should job run in background ?
	if (((is_bg = (*cmd->argv[cmd->argc - 1]) == '&')) != 0)
		cmd->argv[--cmd->argc] == NULL; // Why ?
		// Why ?

	return is_bg;
}

void eval(char *cmdline) {
	int bg;
	struct command cmd;

	printf("Evaluating '%s'\n", cmdline);

	// parse cmdline into cmd structure
	bg = parse(cmdline, &cmd);
	printf("Found command %s\n", cmd.argv[0]);

	// -1 means parse error
	if (bg == -1) return;
	// empty line - ignore
	if (cmd.argv[0] == NULL) return;

	if (cmd.builtin == NONE)
		runSystemCommand(&cmd, bg);
	else
		runBuiltinCommand(&cmd, bg);
}

int main(int argc, char **argv)
{
	char cmdline[MAXLINE]; // buffer for fgets

	while (1)
	{
		printf("%s", prompt);

		if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
			error("fgets error");

		if (feof(stdin)) {
			printf("\n");
			exit(0);
		}

		// remove trailing newline
		cmdline[strlen(cmdline) - 1] = '\0';

		// evaluate command line
		eval(cmdline);
	}
}

/* 
int main(int argc, char const **argv)
{
	printf("Hi there\n");

	// executing an ls command
	char *argv2[] = {"ls", "-la", NULL};
	execvp(argv2[0], argv2);

	printf(".. and done!");
} */