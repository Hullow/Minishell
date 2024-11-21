/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:25 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/21 14:34:42 by cmegret          ###   ########.fr       */
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

void	ft_cd(t_command *cmd, t_shell_state *shell_state)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	// Vérifie si les arguments sont valides
	if (!cmd || !shell_state || !cmd->args)
	{
		fprintf(stderr, "Error: Invalid command or shell state\n");
		shell_state->last_exit_status = 1;
		return ;
	}
	// Obtenir le répertoire courant
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		shell_state->last_exit_status = 1;
		return ;
	}
	// Déterminer le chemin à utiliser
	path = cmd->args[1];
	if (!path || ft_strncmp(path, "~", 2) == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			free(oldpwd);
			shell_state->last_exit_status = 1;
			return ;
		}
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			free(oldpwd);
			shell_state->last_exit_status = 1;
			return ;
		}
		printf("%s\n", path); // Affiche OLDPWD pour `cd -`
	}
	// Effectuer le changement de répertoire
	if (chdir(path) == -1)
	{
		perror("cd");
		free(oldpwd);
		shell_state->last_exit_status = 1;
		return ;
	}
	// Mettre à jour les variables d'environnement
	update_env_var(&shell_state->envp, "OLDPWD", oldpwd);
	free(oldpwd);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("getcwd");
		shell_state->last_exit_status = 1;
		return ;
	}
	update_env_var(&shell_state->envp, "PWD", newpwd);
	free(newpwd);
	// Mettre à jour le statut de sortie
	shell_state->last_exit_status = 0;
}
