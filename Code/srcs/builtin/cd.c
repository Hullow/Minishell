/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/03 22:32:10 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Retrieves the destination path for the cd command.
 *
 * This function determines the destination path based on the command arguments.
 * It handles special cases such as "cd" or "~" to change to the home directory,
 * and "-" to change to the previous directory.
 *
 * @param cmd A pointer to the command structure containing the arguments for
 * the cd command.
 * @param shell_state A pointer to the shell state structure.
 * @return The destination path.
 */
static char	*get_cd_path(t_command *cmd, t_shell_state *shell_state)
{
	char	*path;

	path = cmd->args[1];
	if (!path || ft_strncmp(path, "~", 2) == 0)
		path = get_env_var(shell_state->envp, "HOME");
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = get_env_var(shell_state->envp, "OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	return (path);
}

/**
 * @brief Changes the current working directory.
 *
 * This function changes the current working directory to the specified path.
 * If the chdir function fails, it prints an error message and updates
 * the shell state.
 *
 * @param path The destination path.
 * @param shell_state A pointer to the shell state structure.
 * @return 0 on success, -1 on failure.
 */
static int	change_directory(char *path, t_shell_state *shell_state)
{
	if (chdir(path) == -1)
	{
		ft_print_error("cd", path, "No such file or directory");
		shell_state->last_exit_status = 1;
		return (-1);
	}
	return (0);
}

/**
 * @brief Updates the OLDPWD and PWD environment variables.
 *
 * This function updates the OLDPWD and PWD environment variables
 * based on the current working directory.
 *
 * @param shell_state A pointer to the shell state structure.
 * @param oldpwd The previous working directory.
 */
static void	update_pwd_vars(t_shell_state *shell_state, char *oldpwd)
{
	char	*newpwd;

	update_env_var(&shell_state->envp, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	update_env_var(&shell_state->envp, "PWD", newpwd);
	free(newpwd);
}

/**
 * @brief Changes the current working directory of the shell.
 *
 * This function changes the current working directory based on the provided
 * command arguments. It handles special cases such as "cd" or "~" to change
 * to the home directory, and "-" to change to the previous directory.
 * It updates the shell state and environment variables accordingly.
 *
 * @param cmd A pointer to the command structure containing the arguments
 * for the cd command.
 * @param shell_state A pointer to the shell state structure.
 */
void	ft_cd(t_command *cmd, t_shell_state *shell_state)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
		return ;
	}
	path = get_cd_path(cmd, shell_state);
	if (change_directory(path, shell_state) == -1)
	{
		free(oldpwd);
		return ;
	}
	update_pwd_vars(shell_state, oldpwd);
	shell_state->last_exit_status = 0;
}
