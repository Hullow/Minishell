/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:25 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/12 14:02:39 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

void	ft_cd(struct s_command *cmd, struct s_shell_state *shell_state)
{
	const char	*path;

	path = cmd->args[0];
	if (!path || strcmp(path, "~") == 0)
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
	setenv("OLDPWD", getenv("PWD"), 1); // Change later
	setenv("PWD", shell_state->current_directory, 1); // Change later
}
