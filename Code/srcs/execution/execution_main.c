/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:23:09 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/28 17:23:43 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Handles the execution of a command in a child process.
 *
 * This function is called in the child process after a fork. It attempts to
 * find the path of the command and execute it using execve. If any error
 * occurs, it prints an error message and exits the process.
 *
 * @param cmd A pointer to the command structure containing the command to be
 * executed.
 * @param envp An array of environment variables.
 */
static void	handle_child_process(t_command *cmd_list, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(cmd_list->cmd_name, '/') != NULL)
		cmd_path = cmd_list->cmd_name;
	else
	{
		cmd_path = get_cmd_path(cmd_list->cmd_name, envp);
		if (cmd_path == NULL)
		{
			printf("%s: command not found\n", cmd_list->cmd_name);
			exit(127);
		}
	}
	if (access(cmd_path, F_OK) != 0)
	{
		printf("%s: command not found\n", cmd_list->cmd_name);
		exit(127);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		perror("minishell: permission denied");
		exit(126);
	}
	if (execve(cmd_path, cmd_list->args, envp) == -1)
	{
		free(cmd_path);
		perror("execve failed");
		exit(1);
	}
}

/**
 * @brief Sets up pipes for inter-process communication.
 *
 * This function sets up the necessary pipes for communication between
 * processes. It duplicates file descriptors to set up the standard input
 * and output for the current command.
 *
 * @param fd An array of file descriptors for the pipe.
 * @param in_fd The file descriptor for the input.
 * @param cmd_list A pointer to the command structure containing
 * the command to be
 * executed.
 */
static void	setup_pipes(int *fd, int in_fd, t_command *cmd_list)
{
	if (cmd_list->next != NULL && pipe(fd) == -1)
		error_and_exit("pipe failed", 1);
	if (in_fd != 0)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			error_and_exit("dup2 failed", 1);
		close(in_fd);
	}
	if (cmd_list->next != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error_and_exit("dup2 failed", 1);
		close(fd[1]);
	}
}

/**
 * @brief Handles the parent process after forking.
 *
 * This function is called in the parent process after a fork. It waits for
 * the child process to finish and retrieves its exit status. It also manages
 * the file descriptors for the pipes.
 *
 * @param pid The process ID of the child process.
 * @param fd An array of file descriptors for the pipe.
 * @param in_fd A pointer to the file descriptor for the input.
 * @param cmd_list A pointer to the command structure containing
 * the command to be
 * executed.
 * @return The exit code of the child process.
 */
static int	handle_parent_process(pid_t pid, int *fd,
	int *in_fd, t_command *cmd_list)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd_list->next != NULL)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
	else
		close(fd[0]);
	return (exit_code);
}

/**
 * @brief Executes a list of commands, handling pipes and builtins.
 *
 * This function iterates through a list of commands, checking if each command
 * is a builtin and executing it if it is. If the command is not a builtin, it
 * forks a new process to execute the command. It handles piping between
 * commands, setting up the appropriate file descriptors for input and output.
 * It also manages the parent and child processes, ensuring proper cleanup and
 * error handling.
 *
 * @param cmd_list A pointer to the list of command structures to be executed.
 * @param envp An array of environment variables.
 * @param shell_state A pointer to the shell state structure.
 * @return 0 if all commands were executed successfully,
 * -1 if there was an error.
 */
int	execute_cmd(t_command *cmd_list, char **envp, t_shell_state *shell_state)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd;

	in_fd = 0;
	while (cmd_list)
	{
		if (ft_execute_builtin(cmd_list, shell_state) == 0)
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		setup_pipes(fd, in_fd, cmd_list);
		pid = fork();
		if (pid == 0)
		{
			if (cmd_list->next != NULL)
				close(fd[0]);
			handle_child_process(cmd_list, envp);
		}
		else if (pid < 0)
			error_and_exit("fork failed", 1);
		else
		{
			shell_state->last_exit_status
				= handle_parent_process(pid, fd, &in_fd, cmd_list);
			cmd_list = cmd_list->next;
		}
	}
	return (0);
}
