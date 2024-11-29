/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:51:14 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/28 10:44:55 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Get the old working directory (OLDPWD).
 *
 * This function retrieves the current working directory before changing it.
 *
 * @return A pointer to a string containing the current directory.
 *         Returns NULL and prints an error message if getcwd fails.
 */
char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("getcwd");
	return (oldpwd);
}

/**
 * @brief Change the current working directory.
 *
 * Attempts to change the current working directory to the specified path.
 *
 * @param path The target path to navigate to.
 * @return 0 if successful, 1 if an error occurred.
 */
int	change_directory(const char *path)
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
void	update_environment(t_shell_state *shell_state, char *oldpwd)
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

/**
 * handle_cd_init - Initialise la commande cd.
 * @cmd: Pointeur vers la structure de commande.
 * @shell_state: Pointeur vers l'état du shell.
 * @oldpwd: Pointeur vers une chaîne de caractères pour stocker l'ancien
 * répertoire de travail.
 *
 * Cette fonction vérifie la validité des arguments de la commande et de
 * l'état du shell.
 * Si les arguments sont valides, elle récupère l'ancien répertoire de travail.
 * En cas d'erreur, elle met à jour le statut de sortie du shell et retourne 1.
 * En cas de succès, elle retourne 0.
 *
 * Return: 0 en cas de succès, 1 en cas d'erreur.
 */
int	handle_cd_init(t_command *cmd,
	t_shell_state *shell_state, char **oldpwd)
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
