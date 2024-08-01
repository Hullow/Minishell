/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:17:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/04/19 13:57:46 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_and_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	assign_file_values(int *file1, int *file2, char **argv)
{
	*file1 = open(argv[1], O_RDONLY);
	if (*file1 == -1)
	{
		perror("Error opening file1");
		exit(EXIT_FAILURE);
	}
	*file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*file2 == -1)
	{
		perror("Error opening file2");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	int	file1;
	int	file2;

	if (argc != 5)
		error_and_exit("Wrong number of arguments");
	assign_file_values(&file1, &file2, argv);
	if (pipe(fd) == -1)
		error_and_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_and_exit("fork");
	if (pid == 0)
	{
		child_process(fd, file1, argv, envp);
	}
	else
	{
		parent_process(fd, file2, argv, envp);
	}
	close_files(file1, file2, fd);
	return (0);
}
