/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:25 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/21 14:47:48 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Changes the current working directory of the shell.
 *
 * This function changes the current working directory based on the provided
 * command arguments. It handles special cases such as "cd" or "~" to change
 * to the home directory, and ".." to change to the previous directory.
 * It updates the shell state and environment variables accordingly.
 *
 * @param cmd A pointer to the command structure containing
 *            the arguments for the cd command.
 * @param shell_state A pointer to the shell state structure.
 *
 * @note If the path is "cd" or "~", it changes to the home directory.
 * @note If the path is "..", it changes to the previous directory.
 * @note If the chdir function fails, it prints an error message and returns.
 * @note It updates the current working directory in the shell state.
 * @note It updates the OLDPWD and PWD environment variables.
 */

/* void	ft_cd(t_command *cmd, t_shell_state *shell_state)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	path = cmd->args[1];
	oldpwd = getcwd(NULL, 0);
	if (!path || ft_strncmp(path, "~", 2) == 0)
		path = getenv("HOME");
	else if (ft_strncmp(path, "..", 3) == 0)
		path = "..";
	if (chdir(path) == -1)
	{
		perror("cd");
		shell_state->last_exit_status = 1;
		free(oldpwd);
		return ;
	}
	update_env_var(&shell_state->envp, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	update_env_var(&shell_state->envp, "PWD", newpwd);
	free(newpwd);
	shell_state->last_exit_status = 0;
} */

/**
 * @brief Get the old working directory (OLDPWD).
 *
 * This function retrieves the current working directory before changing it.
 *
 * @return A pointer to a string containing the current directory.
 *         Returns NULL and prints an error message if getcwd fails.
 */
static char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("getcwd");
	return (oldpwd);
}

/**
 * @brief Determine the target path for the cd command.
 *
 * This function determines the path to which the shell should navigate,
 * handling special cases such as "~" for the home directory and "-" for OLDPWD.
 *
 * @param args The arguments for the cd command.
 * @return A pointer to the target path as a string.
 */
static char	*get_target_path(char **args)
{
	char	*path;

	path = args[1];
	if (!path || ft_strncmp(path, "~", 2) == 0)
		path = getenv("HOME");
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = getenv("OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	return (path);
}

/**
 * @brief Change the current working directory.
 *
 * Attempts to change the current working directory to the specified path.
 *
 * @param path The target path to navigate to.
 * @return 0 if successful, 1 if an error occurred.
 */
static int	change_directory(const char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

/**
 * @brief Update the shell's environment variables for PWD and OLDPWD.
 *
 * This function updates the OLDPWD and PWD environment variables
 * after a successful directory change.
 *
 * @param shell_state The current shell state structure.
 * @param oldpwd The previous working directory.
 */
static void	update_environment(t_shell_state *shell_state, char *oldpwd)
{
	char	*newpwd;

	update_env_var(&shell_state->envp, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("getcwd");
		return ;
	}
	update_env_var(&shell_state->envp, "PWD", newpwd);
	free(newpwd);
}

static int	handle_cd_init(t_command *cmd, t_shell_state *shell_state, char **oldpwd)
{
	if (!cmd || !shell_state || !cmd->args)
	{
		fprintf(stderr, "Error: Invalid command or shell state\n");
		shell_state->last_exit_status = 1;
		return (1);
	}
	*oldpwd = get_oldpwd();
	if (!*oldpwd)
	{
		shell_state->last_exit_status = 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Execute the cd command.
 *
 * Changes the current directory based on the provided command arguments,
 * updates the environment variables, and handles errors appropriately.
 *
 * @param cmd The command structure containing the arguments.
 * @param shell_state The shell state structure.
 */
void	ft_cd(t_command *cmd, t_shell_state *shell_state)
{
	char	*path;
	char	*oldpwd;

	if (handle_cd_init(cmd, shell_state, &oldpwd))
		return ;
	path = get_target_path(cmd->args);
	if (!path)
	{
		fprintf(stderr, "cd: Target path not set\n");
		free(oldpwd);
		shell_state->last_exit_status = 1;
		return ;
	}
	if (change_directory(path))
	{
		free(oldpwd);
		shell_state->last_exit_status = 1;
		return ;
	}
	update_environment(shell_state, oldpwd);
	free(oldpwd);
	shell_state->last_exit_status = 0;
}
