/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/02 16:19:34 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

char	*get_env_var(char **envp, char *key)
{
	size_t	key_len;
	int		index;

	key_len = strlen(key);
	index = find_var_index(envp, key, key_len);
	if (index != -1)
		return (envp[index] + key_len + 1);
	return (NULL);
}

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
void	ft_cd(t_command *cmd, t_shell_state *shell_state)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	path = cmd->args[1];
	oldpwd = getcwd(NULL, 0);
	if (!path || ft_strncmp(path, "~", 2) == 0)
		path = get_env_var(shell_state->envp, "HOME");
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = get_env_var(shell_state->envp, "OLDPWD");
		if (path)
			printf("%s\n", path);
	}
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
}
