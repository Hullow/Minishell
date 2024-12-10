/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:04 by cmegret          #+#    #+#             */
/*   Updated: 2024/12/10 17:30:04 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Waits for all processes in the pipeline to finish.
 *
 * This function waits for each process in the pipeline to finish
 * and collects their exit statuses.
 *
 * @param pipeline_pids An array of PIDs of the processes in the pipeline.
 * @param pid_count The number of processes in the pipeline.
 */
void	wait_for_pipeline(pid_t *pipeline_pids, int pid_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < pid_count)
	{
		if (pipeline_pids[i] > 0)
			if (waitpid(pipeline_pids[i], &status, 0) == -1)
				perror("waitpid");
		i++;
	}
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
pid_t	execute_pipeline(t_command *cmd_list,
	t_shell_state *shell_state, int in_fd, int *next_in_fd)
{
	int		fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	if (cmd_list->next)
		if (pipe(fd) == -1)
			error_and_exit("pipe failed", 1);
	pid = fork();
	if (pid == 0)
		execute_child(cmd_list, shell_state, in_fd, fd);
	else if (pid < 0)
		error_and_exit("fork failed", 1);
	else
		handle_parent(in_fd, fd);
	if (cmd_list->next)
		*next_in_fd = fd[0];
	else
		*next_in_fd = 0;
	return (pid);
}
