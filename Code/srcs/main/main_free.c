/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:59:44 by fallan            #+#    #+#             */
/*   Updated: 2024/12/18 12:04:10 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Frees the prompt, the token list, and the command list
void	ft_free_all(char *prompt, t_token *token_list, t_command *cmd)
{
	free(prompt);
	ft_free_token_list(token_list);
	ft_free_cmd_list(cmd);
}

// frees the whole list of commands
// calls the required functions to free the contents within each node
// (redirections, arguments list, arguments array)
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

// free the array of command arguments (char **args) of a command list node
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

// frees the linked list of command arguments
// within each node:
//	- frees the string, if present
//  - frees the expansion marker t_expand linked list, if present
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

// frees a redirection linked list
// and for each node, frees the heredoc linked list inside (if present)
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
