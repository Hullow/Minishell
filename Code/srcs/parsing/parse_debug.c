/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:06:55 by francis           #+#    #+#             */
/*   Updated: 2024/11/29 15:52:34 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// prints all command arguments from the array of arguments of a command sequence
void	ft_print_args(t_command *cmd_sequence)
{
	int	i;

	i = -1;
	// printf("ft_print_args:\n");
	if (cmd_sequence && cmd_sequence->args)
	{
		while (cmd_sequence->args[++i])
			printf("\targ[%d]: [%s]\n", i, cmd_sequence->args[i]);
	}
	return ;
}

// returns the type of redirection (int to string)
char	*ft_return_redir_type(int redir_type)
{
	if (redir_type == REDIR_APPEND)
		return("REDIR_APPEND");
	else if (redir_type == REDIR_INPUT)
		return("REDIR_INPUT");
	else if (redir_type == REDIR_OUTPUT)
		return("REDIR_OUTPUT");
	else if (redir_type == REDIR_HEREDOC)
		return("REDIR_HEREDOC");
	else
		return (NULL);
}

// prints redirection number, type, and destination/origin/delimiter
int	ft_print_redirs(t_redir *redir_list)
{
	t_redir	*head;
	int	i;

	if (!redir_list)
	{
		printf("\tno redirections\n");
		return (0);
	}
	head = redir_list;
	i = 1;
	while (redir_list)
	{
		printf("\tredirection %d is of type: {%s} to/from/delimiter {%s}\n", i, ft_return_redir_type(redir_list->type), redir_list->str);
		redir_list = redir_list->next;
		i++;
	}
	redir_list = head;
	return (i);
}

// print all command sequences: command name, command arguments, redirections
void	ft_print_command_sequences(t_command *head)
{
	printf("command sequences:\n");
	while (head)
	{
		printf("*****\n - command: {%s}\n – arguments:\n", head->cmd_name);
		ft_print_args(head);
		printf(" – redirections:\n");
		ft_print_redirs(head->redir_list);
		head = head->next;
	}
}
