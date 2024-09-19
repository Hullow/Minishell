/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:25 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/19 14:54:12 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

/**
 * ft_cd - Changes the current working directory of the shell.
 *
 * This function changes the current working directory based on the provided
 * command arguments. It handles special cases such as "cd" or "~" to change
 * to the home directory, and ".." to change to the previous directory.
 * It updates the shell state and environment variables accordingly.
 *
 * Parameters:
 *   cmd - A pointer to the command structure containing
 *   the arguments for the cd command.
 *   shell_state - A pointer to the shell state structure.
 *
 * Notes:
 *   - If the path is "cd" or "~", it changes to the home directory.
 *   - If the path is "..", it changes to the previous directory.
 *   - If the chdir function fails, it prints an error message and returns.
 *   - It updates the current working directory in the shell state.
 *   - It updates the OLDPWD and PWD environment variables.
 */
void	ft_cd(struct s_command *cmd, struct s_shell_state *shell_state)
{
	char	*path;

	path = cmd->args[1];
	if (ft_strncmp(path, "cd", 3) == 0 || ft_strncmp(path, "~", 2) == 0)
		path = getenv("HOME");
	else if (ft_strncmp(path, "..", 2) == 0)
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
