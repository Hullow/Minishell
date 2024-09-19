/*

Certainly, I can outline the architecture and functioning of a mini-shell programmed in C. Here's a high-level overview:

1. Main Loop:
   - The shell runs in an infinite loop, continually prompting for and executing commands.

2. Input Processing:
   - Read user input using functions like `fgets()` or `readline()`.
   - Parse the input to separate the command and its arguments.

3. Command Execution:
   - Fork a child process using `fork()`.
   - In the child process, use `execvp()` or similar to execute the command.
   - The parent process waits for the child to complete using `wait()` or `waitpid()`.

4. Built-in Commands:
   - Implement basic built-in commands like `cd`, `exit`, `help`.

5. Error Handling:
   - Implement robust error checking and reporting.

6. Signal Handling:
   - Set up signal handlers for signals like SIGINT (Ctrl+C).

Here's a basic skeleton of how this might look in C:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void execute_command(char **args);
int builtin_command(char **args);

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    
    while (1) {
        printf("mini-shell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Parse input
        char *token = strtok(input, " \n");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;
        
        if (args[0] != NULL) {
            if (!builtin_command(args)) {
                execute_command(args);
            }
        }
    }
    
    return 0;
}

void execute_command(char **args) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("mini-shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("mini-shell");
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int builtin_command(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "mini-shell: expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("mini-shell");
            }
        }
        return 1;
    }
    return 0;
}

