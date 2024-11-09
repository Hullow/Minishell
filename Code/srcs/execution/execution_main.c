/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:23:09 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/09 16:25:43 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Checks if the command is a builtin and executes it.
 *
 * This function checks if the given command corresponds to a builtin command.
 * If it does, it calls the appropriate sub-function to execute the builtin
 * command and returns 0. Otherwise, it returns 1.
 *
 * @param cmd A pointer to the command structure containing the command
 * to be checked.
 * @param shell_state A pointer to the shell state structure.
 * @return 0 if the command is a builtin and was executed, 1 otherwise.
 */
int	ft_is_and_execute_builtin(t_command *cmd, t_shell_state *shell_state)
{
	if (ft_execute_echo(cmd, shell_state) == 0)
		return (0);
	else if (ft_execute_cd(cmd, shell_state) == 0)
		return (0);
	else if (ft_execute_pwd(cmd, shell_state) == 0)
		return (0);
	else if (ft_execute_export(cmd, shell_state) == 0)
		return (0);
	else if (ft_execute_unset(cmd, shell_state) == 0)
		return (0);
	else if (ft_execute_env(cmd, shell_state) == 0)
		return (0);
	else if (ft_execute_exit(cmd, shell_state) == 0)
		return (0);
	return (1);
}

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
			error_and_exit("get_cmd_path");
	}
	if (execve(cmd_path, cmd_list->args, envp) == -1)
	{
		free(cmd_path);
		error_and_exit("execve");
	}
}

static void	setup_pipes(int *fd, int in_fd, t_command *cmd_list)
{
	if (cmd_list->next != NULL)
	{
		if (pipe(fd) == -1)
			error_and_exit("pipe");
	}
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd_list->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

static int	handle_parent_process(pid_t pid, int *fd, int *in_fd,
				t_command *cmd_list)
{
	int	status;
	int	exit_code;

	exit_code = -1;
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
		if (ft_is_and_execute_builtin(cmd_list, shell_state) == 0)
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		setup_pipes(fd, in_fd, cmd_list);
		pid = fork();
		if (pid == 0)
			handle_child_process(cmd_list, envp);
		else if (pid < 0)
			error_and_exit("fork");
		else
		{
			shell_state->last_exit_status
				= handle_parent_process(pid, fd, &in_fd, cmd_list);
			cmd_list = cmd_list->next;
		}
	}
	return (0);
}
