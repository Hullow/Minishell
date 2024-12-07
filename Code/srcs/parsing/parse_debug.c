/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:06:55 by francis           #+#    #+#             */
/*   Updated: 2024/12/07 14:34:59 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// prints all command arguments 
// from the array of arguments of a command sequence
void	ft_print_args(t_command *cmd_list)
{
	int	i;

	i = -1;
	// printf("ft_print_args:\n");
	if (cmd_list && cmd_list->args)
	{
		while (cmd_list->args[++i])
			printf(" – arg[%d]: {%s}", i, cmd_list->args[i]);
	}
	return ;
}

// returns the type of redirection (int to string)
char	*ft_return_redir_type(int redir_type)
{
	if (redir_type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (redir_type == REDIR_INPUT)
		return ("REDIR_INPUT");
	else if (redir_type == REDIR_OUTPUT)
		return ("REDIR_OUTPUT");
	else if (redir_type == REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	else
		return (NULL);
}

// prints redirection number, type, and destination/origin/delimiter
int	ft_print_redirs(t_redir *redir_list)
{
	t_redir	*head;
	int		i;

	if (!redir_list)
	{
		printf("\tno redirections\n");
		return (0);
	}
	head = redir_list;
	i = 1;
	while (redir_list)
	{
		printf("\tredirection %d is of type: {%s} to/from/delimiter {%s}\n", \
			i, ft_return_redir_type(redir_list->type), redir_list->str);
		redir_list = redir_list->next;
		i++;
	}
	redir_list = head;
	return (i);
}

// derived from ft_print_command_sequences: 
// stops the "exit bug" from happening on (ARM) OS X
void	ft_exit_bug_print_debugger(t_command *head)
{
	int	i;

	i = -1;
	while (head)
	{
		printf("%s", head->cmd_name);
		while (++i < (int) ft_strlen(head->cmd_name))
			printf("\b"); // removes previous characters
		i = -1;
		head = head->next;
	}
	// printf("head address after: {%p}\n", head);
		// this can make the bug reappear in some cases!
}

// prints the command in each pipe, its arguments and redirections
void	ft_print_command_sequences(t_command *head)
{
	printf("command sequences:\n");
	while (head)
	{
		printf("*****\n - command: {%s}\n", head->cmd_name);
		printf(" – arguments:\n");
		ft_print_args(head);
		printf("\n – redirections:\n");
		ft_print_redirs(head->redir_list);
		head = head->next;
	}
}

// Used to debug "exit bug" 
/* t_command *ft_debug_parsing(t_token *tok)
{
	t_command	*cmd_list;
	int			i;

	cmd_list = malloc (sizeof(t_command));
	if (!cmd_list)
		return (NULL);
	if (tok && tok->type == END_OF_INPUT)
		printf("end of input token tokenized\n");
	cmd_list->args = malloc (2 * sizeof(char *));
	if (tok && tok->str)
	{
		cmd_list->cmd_name = ft_strdup(tok->str);
		cmd_list->args[0] = ft_strdup(tok->str);
		tok = tok->next;
	}
	if (cmd_list->cmd_name == NULL || ft_strlen(cmd_list->cmd_name) == 0) 
		return (NULL);
	i = 1;
	while (tok)
	{	
		cmd_list->args = realloc (cmd_list->args, (i + 2) * sizeof(char *));
		if (tok->str)
			cmd_list->args[i] = ft_strdup(tok->str);
		else
		{
			printf("ft_debug – tok: {%p}, no tok->str\n", tok);
			cmd_list->args[i] = NULL;
			return (cmd_list);
		}
		i++;
		tok = tok->next;
	}
	cmd_list->args[i] = NULL;
	ft_print_command_sequences(cmd_list);
	return (cmd_list);
}
 */