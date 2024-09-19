/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:29:53 by cmegret           #+#    #+#             */
/*   Updated: 2024/04/18 14:32:30 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int *fd, int file1, char **argv, char **envp)
{
	close(fd[0]);
	dup2(file1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execute_cmd(argv[2], envp);
}

void	parent_process(int *fd, int file2, char **argv, char **envp)
{
	close(fd[1]);
	wait(NULL);
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	execute_cmd(argv[3], envp);
}

void	close_files(int file1, int file2, int *fd)
{
	close(file1);
	close(file2);
	close(fd[0]);
	close(fd[1]);
}
