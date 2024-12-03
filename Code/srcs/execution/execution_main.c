/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 08:30:46 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Handles the parent process after a fork.
 *
 * This function closes the write end of the pipe,
 * closes the input file descriptor if it is not 0,
 * and waits for the child process to finish.
 *
 * @param pid The PID of the child process.
 * @param in_fd The input file descriptor.
 * @param fd The array of file descriptors for the pipe.
 */
void	handle_parent(pid_t pid, int in_fd, int *fd)
{
	close(fd[1]);
	if (in_fd != 0)
		close(in_fd);
	waitpid(pid, NULL, 0);
}

/**
 * @brief Executes the child process.
 *
 * This function redirects file descriptors for input and output,
 * closes unused file descriptors, and executes either a builtin command
 * or a child process.
 *
 * @param cmd_list The list of commands to execute.
 * @param shell_state The current state of the shell.
 * @param in_fd The input file descriptor.
 * @param fd The array of file descriptors for the pipe.
 */
void	execute_child(t_command *cmd_list,
	t_shell_state *shell_state, int in_fd, int *fd)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd_list->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	close(fd[0]);
	if (ft_is_builtin(cmd_list->cmd_name) == 0)
		ft_execute_builtin(cmd_list, shell_state);
	else
		handle_child_process(cmd_list, shell_state->envp);
	exit(shell_state->last_exit_status);
}

/**
 * @brief Executes a pipeline of commands.
 *
 * This function creates a pipe if necessary, forks a child process,
 * and handles the parent and child processes accordingly.
 *
 * @param cmd_list The list of commands to execute.
 * @param shell_state The current state of the shell.
 * @param in_fd The input file descriptor.
 * @return The output file descriptor of the pipe or 0.
 */
int	execute_pipeline(t_command *cmd_list,
	t_shell_state *shell_state, int in_fd)
{
	int		fd[2];
	pid_t	pid;

	if (cmd_list->next && pipe(fd) == -1)
		error_and_exit("pipe failed", 1);
	pid = fork();
	if (pid == 0)
		execute_child(cmd_list, shell_state, in_fd, fd);
	else if (pid < 0)
		error_and_exit("fork failed", 1);
	else
		handle_parent(pid, in_fd, fd);
	if (cmd_list->next)
		return (fd[0]);
	return (0);
}

/**
 * @brief Executes a list of commands.
 *
 * This function iterates through the list of commands, executes each pipeline
 * of commands, and handles builtin commands.
 *
 * @param cmd_list The list of commands to execute.
 * @param shell_state The current state of the shell.
 * @return 0 on success.
 */
int	execute_cmd(t_command *cmd_list, t_shell_state *shell_state)
{
	int	in_fd;

	in_fd = 0;
	while (cmd_list)
	{
		if (handle_parent_builtin(cmd_list, shell_state) == 0)
			return (0);
		in_fd = execute_pipeline(cmd_list, shell_state, in_fd);
		cmd_list = cmd_list->next;
	}
	return (0);
}
