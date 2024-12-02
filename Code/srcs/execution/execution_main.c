/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/02 16:53:19 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

static void	handle_child_process(t_command *cmd_list, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(cmd_list->cmd_name, '/') != NULL)
		cmd_path = cmd_list->cmd_name;
	else
	{
		cmd_path = get_cmd_path(cmd_list->cmd_name, envp);
		if (cmd_path == NULL)
		{
			printf("%s: command not found\n", cmd_list->cmd_name);
			exit(127);
		}
	}
	if (access(cmd_path, F_OK) != 0)
	{
		printf("%s: No such file or directory\n", cmd_list->cmd_name);
		exit(127);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		printf("minishell: %s: Permission denied\n", cmd_list->cmd_name);
		exit(126);
	}
	if (execve(cmd_path, cmd_list->args, envp) == -1)
	{
		free(cmd_path);
		perror("minishell");
		exit(1);
	}
}

int	execute_cmd(t_command *cmd_list, char **envp, t_shell_state *shell_state)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd = 0; // Entrée par défaut (STDIN)

	while (cmd_list)
	{
		// Si c'est un builtin à exécuter dans le parent et qu'il n'y a pas de pipe
		if (cmd_list->next == NULL && ft_is_builtin(cmd_list->cmd_name) == 0)
		{
			ft_execute_builtin(cmd_list, shell_state);
			return (0);
		}
		// Création du pipe si une commande suivante existe
		if (cmd_list->next && pipe(fd) == -1)
			error_and_exit("pipe failed", 1);
		pid = fork();
		if (pid == 0)
		{
			// Processus enfant
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (cmd_list->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			close(fd[0]); // Ferme les descripteurs inutilisés
			// Exécuter le builtin ou une commande externe
			if (ft_is_builtin(cmd_list->cmd_name) == 0)
				ft_execute_builtin(cmd_list, shell_state);
			else
				handle_child_process(cmd_list, envp);
			exit(shell_state->last_exit_status);
		}
		else if (pid < 0)
			error_and_exit("fork failed", 1);
		else
		{
			// Processus parent
			close(fd[1]); // Ferme le côté écriture du pipe
			if (in_fd != 0)
				close(in_fd);
			in_fd = fd[0]; // Prépare l'entrée pour la commande suivante
			waitpid(pid, &(shell_state->last_exit_status), 0);
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}
