/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:59:44 by fallan            #+#    #+#             */
/*   Updated: 2024/12/18 12:46:37 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Frees all allocated memory used by the shell
 *
 * Deallocates memory for:
 * - The prompt string
 * - The token list
 * - The command list and all its components
 *
 * @param prompt The prompt string to free
 * @param token_list The list of tokens to free
 * @param cmd The command list to free
 */
void	ft_free_all(char *prompt, t_token *token_list, t_command *cmd)
{
	free(prompt);
	ft_free_token_list(token_list);
	ft_free_cmd_list(cmd);
}

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
		i++;
	}
	free(args);
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
	t_expand	*temp_expand;

	temp = NULL;
	temp_expand = NULL;
	while (arg_list)
	{
		temp = arg_list;
		if (arg_list->arg_string)
			free(arg_list->arg_string);
		while (arg_list->to_expand)
		{
			temp_expand = arg_list->to_expand;
			arg_list->to_expand = arg_list->to_expand->next;
			free(temp_expand);
		}
		arg_list = arg_list->next;
		free(temp);
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
		while (redir_list->heredoc)
		{
			temp_heredoc = redir_list->heredoc;
			redir_list->heredoc = redir_list->heredoc->next;
			free(temp_heredoc);
		}
		redir_list = redir_list->next;
		free(temp_redir);
	}
}
