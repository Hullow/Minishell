/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:25 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/19 14:25:04 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

void	ft_cd(struct s_command *cmd, struct s_shell_state *shell_state)
{
	char	*path;

	path = cmd->args[1];
	if (ft_strncmp(path, "cd", 3) == 0 || strcmp(path, "~") == 0)
		path = getenv("HOME");
	else if (strcmp(path, "-") == 0)
		path = getenv("OLDPWD");
	if (chdir(path) == -1)
	{
		perror("Error with the cd command");
		return ;
	}
	free(shell_state->current_directory);
	shell_state->current_directory = getcwd(NULL, 0);
	if (!shell_state->current_directory)
		error_and_exit("getcwd failed");
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", shell_state->current_directory, 1);
}
