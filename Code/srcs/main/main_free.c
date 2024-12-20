/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:59:44 by fallan            #+#    #+#             */
/*   Updated: 2024/12/20 17:08:07 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Frees an entire command list structure
 *
 * Recursively frees all components of each command node:
 * - Redirection list
 * - Argument list
 * - Arguments array
 * - Command node itself
 *
 * @param cmd Pointer to the first command node
 */
void	ft_free_cmd_list(t_command *cmd)
{
	t_command	*temp_cmd;

	while (cmd)
	{
		temp_cmd = cmd;
		ft_free_redir_list(cmd->redir_list);
		ft_free_arg_list(cmd->arg_list);
		ft_free_cmd_args(cmd->args);
		cmd = cmd->next;
		free(temp_cmd);
		temp_cmd = NULL;
	}
}

/**
 * @brief Frees an array of command arguments
 *
 * Deallocates memory for:
 * - Each individual argument string
 * - The array itself
 *
 * @param args NULL-terminated array of argument strings
 */
void	ft_free_cmd_args(char **args)
{
	int			i;
	char		*temp_arg;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		temp_arg = args[i];
		free(temp_arg);
		temp_arg = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

/**
 * @brief Frees a linked list of command arguments
 *
 * For each argument node, deallocates:
 * - The argument string
 * - The expansion markers list
 * - The node itself
 *
 * @param arg_list Pointer to the first argument node
 */
void	ft_free_arg_list(t_cmd_args	*arg_list)
{
	t_cmd_args	*temp;

	temp = NULL;
	while (arg_list)
	{
		temp = arg_list;
		if (arg_list->arg_string)
			free(arg_list->arg_string);
		arg_list->arg_string = NULL;
		arg_list = arg_list->next;
		free(temp);
		temp = NULL;
	}
}

/**
 * @brief Frees a redirection list structure
 *
 * For each redirection node, deallocates:
 * - The heredoc linked list if present
 * - The redirection node itself
 *
 * @param redir_list Pointer to the first redirection node
 */
void	ft_free_redir_list(t_redir *redir_list)
{
	t_redir		*temp_redir;
	t_heredoc	*temp_heredoc;

	while (redir_list)
	{
		temp_redir = redir_list;
		if (redir_list->str)
			free(redir_list->str);
		redir_list->str = NULL;
		while (redir_list->heredoc)
		{
			temp_heredoc = redir_list->heredoc;
			redir_list->heredoc = redir_list->heredoc->next;
			free(temp_heredoc->line);
			free(temp_heredoc);
			temp_heredoc->line = NULL;
			temp_heredoc = NULL;
		}
		redir_list = redir_list->next;
		free(temp_redir);
		temp_redir = NULL;
	}
}

void	ft_free_shell_state(t_shell_state *shell_state)
{
	int	i;

	if (!shell_state)
		return ;
	i = 0;
	if (shell_state->envp)
	{
		while (shell_state->envp[i])
		{
			free(shell_state->envp[i]);
			shell_state->envp[i] = NULL;
			i++;
		}
		free(shell_state->envp);
		shell_state->envp = NULL;
	}
}
