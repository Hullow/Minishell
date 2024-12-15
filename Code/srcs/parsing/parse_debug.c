/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:06:55 by francis           #+#    #+#             */
/*   Updated: 2024/12/15 16:28:01 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// prints all command arguments 
// from the array of arguments of a command sequence
void	ft_print_args(t_command *cmd)
{
	int	i;

	i = -1;
	printf("ft_print_args:\n");
	if (cmd && cmd->args)
	{
		while (cmd->args[++i])
		{
			printf(" – arg[%d]: {%s} ", i, cmd->args[i]);
			if (cmd->args_between_quotes[i] == 2)
				printf("(double quoted)");
			else if (cmd->args_between_quotes[i] == 1)
				printf("(single quoted)");
			else if (cmd->args_between_quotes[i] == 0)
				printf("(not quoted)");
			else
				printf("(!!quote status error!!)");
		}
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

// prints all redirections in a redirection linked list (i.e. for a single command/pipe) 
void	ft_print_redirs(t_redir *redir, char *cmd_name)
{
	int	i;

	i = 0;
	printf("redirections for the command {%s}\n", cmd_name);
	while (redir)
	{
		printf("\t- redirection %d is of type: {%s} to/from/delimiter {%s} ", \
			i, ft_return_redir_type(redir->type), redir->str);
		if (redir->type == REDIR_HEREDOC)
		{
			if (redir->expand_heredoc)
				printf("(not quoted: expand in heredoc)\n");
			else
				printf("(quoted: don't expand in heredoc)\n");
		}
		redir = redir->next;
		i++;
	}
}

// prints redirection number, type, and destination/origin/delimiter
void	ft_print_all_redirs(t_command *cmd)
{
	t_redir	*redir;

	printf("ft_print_all_redirs:\n");
	while (cmd)
	{
		if (!(cmd->redir_list))
		{
			printf("\tno redirections\n");
			return ;
		}
		redir = cmd->redir_list;
		printf("redirections for cmd {%s}\n", cmd->cmd_name);
		ft_print_redirs(redir, cmd->cmd_name);
		cmd = cmd->next;
	}
}

// prints the command in each pipe, its arguments and redirections
void	ft_print_command_sequences(t_command *cmd)
{
	printf("command sequences:\n");
	while (cmd)
	{
		printf("*****\n - command: {%s}\n", cmd->cmd_name);
		printf(" – arguments:\n");
		ft_print_args(cmd);
		printf("\n – redirections:\n");
		cmd = cmd->next;
		ft_print_redirs(cmd->redir_list, cmd->cmd_name);
	}
}

/* // derived from ft_print_command_sequences: 
// stops the "exit bug" from happening on (ARM) OS X
// How it works:
//		printf("%s", head->cmd_name);
//			=> print the cmd_name variable
// 		while (++i < (int) ft_strlen(head->cmd_name))
//			printf("\b");
//			=> erase each printed character using printf("\b");
//	N.b.: in some cases, this code at the end of the function
// 	makes the bug reappear:
		// printf("head address after: {%p}\n", head);
		// this can make the bug reappear in some cases!
void	ft_exit_bug_print_debugger(t_command *head)
{
	int	i;

	i = -1;
	while (head)
	{
		printf("%s", head->cmd_name);
		while (++i < (int) ft_strlen(head->cmd_name))
			printf("\b");
		i = -1;
		head = head->next;
	}
}
 */