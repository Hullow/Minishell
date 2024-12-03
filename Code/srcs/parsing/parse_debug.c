/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:06:55 by francis           #+#    #+#             */
/*   Updated: 2024/12/03 07:47:14 by cmegret          ###   ########.fr       */
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
			printf(" – arg[%d]: {%s}", i, cmd_sequence->args[i]);
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

// derived from ft_print_command_sequences: 
// stops the "exit bug" from happening on (ARM) OS X
void	ft_exit_bug_print_debugger(t_command *head)
{
	int	i = -1;

	while (head)
	{
		printf("%s", head->cmd_name);
		while (++i < (int) ft_strlen(head->cmd_name))
			printf("\b"); // removes previous characters
		i = -1;
		head = head->next;
	}
	// printf("head address after: {%p}\n", head); // this can make the bug reappear in some cases!
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
	t_command	*cmd_sequence;
	int			i;

	cmd_sequence = malloc (sizeof(t_command));
	if (!cmd_sequence)
		return (NULL);
	if (tok && tok->type == END_OF_INPUT)
		printf("end of input token tokenized\n");
	cmd_sequence->args = malloc (2 * sizeof(char *));
	if (tok && tok->str)
	{
		cmd_sequence->cmd_name = ft_strdup(tok->str);
		cmd_sequence->args[0] = ft_strdup(tok->str);
		tok = tok->next;
	}
	if (cmd_sequence->cmd_name == NULL || ft_strlen(cmd_sequence->cmd_name) == 0) // or ft_strlen ((*cmd_sequence)->cmd_name == NULL))
		return (NULL);
	i = 1;
	while (tok)
	{	
		cmd_sequence->args = realloc (cmd_sequence->args, (i + 2) * sizeof(char *));
		if (tok->str)
			cmd_sequence->args[i] = ft_strdup(tok->str);
		else
		{
			printf("ft_debug – tok: {%p}, no tok->str\n", tok);
			cmd_sequence->args[i] = NULL;
			return (cmd_sequence);
		}
		i++;
		tok = tok->next;
	}
	cmd_sequence->args[i] = NULL;
	ft_print_command_sequences(cmd_sequence);
	return (cmd_sequence);
}
 */