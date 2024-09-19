/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:23:11 by cmegret           #+#    #+#             */
/*   Updated: 2024/04/19 13:57:49 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>

int		main(int argc, char **argv, char **envp);
int		ft_strncmp(char *s1, char *s2, size_t n);

void	error_and_exit(char *msg);
void	execute_cmd(char *cmd, char **envp);
void	close_files(int file1, int file2, int *fd);
void	assign_file_values(int *file1, int *file2, char **argv);
void	child_process(int *fd, int file1, char **argv, char **envp);
void	parent_process(int *fd, int file2, char **argv, char **envp);

char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif