/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:57 by francis           #+#    #+#             */
/*   Updated: 2024/12/27 17:17:58 by francis          ###   ########.fr       */
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
		ft_free_array_of_strings(cmd->args);
		if (cmd->saved_input > 2)
			close(cmd->saved_input);
		if (cmd->saved_output > 2)
			close(cmd->saved_output);
		cmd = cmd->next;
		free(temp_cmd);
	}
}

/**
 * @brief Frees an array of string
 *
 * Deallocates memory for:
 * - Each individual string in the array
 * - The array itself
 *
 * @param args NULL-terminated array of strings
 */
void	ft_free_array_of_strings(char **args)
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

	temp = NULL;
	while (arg_list)
	{
		temp = arg_list;
		if (arg_list->arg_string)
			free(arg_list->arg_string);
		arg_list->arg_string = NULL;
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
		if (redir_list->str)
			free(redir_list->str);
		while (redir_list->heredoc)
		{
			temp_heredoc = redir_list->heredoc;
			redir_list->heredoc = redir_list->heredoc->next;
			free(temp_heredoc->line);
			free(temp_heredoc);
		}
		redir_list = redir_list->next;
		free(temp_redir);
	}
}
