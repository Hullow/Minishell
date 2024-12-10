/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:28:03 by fallan            #+#    #+#             */
/*   Updated: 2024/12/10 18:53:46 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// traverses the linked list of tokens and returns the head token
// if redir_list or its "->next" is NULL, returns it
// else, set head to start of the list, then traverses it
// in order to change the heap address of redir_list
t_redir	*ft_last_redir(t_redir **redir_list)
{
	t_redir	*head_redir;

	if (!(*redir_list) || !(*redir_list)->next)
		return (*redir_list);
	head_redir = *redir_list;
	while ((*redir_list)->next)
		(*redir_list) = (*redir_list)->next;
	return (head_redir);
}

// copies the string from our token to the redirection node
// advances by one token in the token linked list
// returns the token
t_token	**ft_assign_redir_str(t_token **tok, t_redir *redir_list)
{
	*tok = (*tok)->next;
	redir_list->str = ft_strdup((*tok)->str);
	if (!redir_list->str)
		return (NULL);
	redir_list->str_type = (*tok)->type;
	return (tok);
}

// if we have redirections, goes to last redirection
// mallocs a new redirection
// sets the type of the redirection
// if there is a token after the redirection,
// call ft_assign_redir_str to assign a string and string type to redirection,
// and advance one token (ft_assign_redir does this)
// N.b.: head_redir is initialized to NULL by the calling function
int	ft_add_redir(t_token **tok, t_command *cmd_list, t_redir *head_redir)
{
	if (cmd_list->redir_list)
	{
		head_redir = ft_last_redir(&(cmd_list->redir_list));
		cmd_list->redir_list->next = malloc (sizeof(t_redir));
		if (!(cmd_list->redir_list->next))
			return (-1);
		cmd_list->redir_list = cmd_list->redir_list->next;
	}
	else
	{
		cmd_list->redir_list = malloc (sizeof(t_redir));
		head_redir = cmd_list->redir_list;
	}
	if (!cmd_list->redir_list)
		return (-1);
	cmd_list->redir_list->type = (*tok)->type;
	cmd_list->redir_list->next = NULL;
	if ((*tok)->next)
		tok = ft_assign_redir_str(tok, cmd_list->redir_list);
	else
		cmd_list->redir_list->str = NULL;
	if (!tok)
		return (-1);
	cmd_list->redir_list = head_redir;
	return (0);
}
