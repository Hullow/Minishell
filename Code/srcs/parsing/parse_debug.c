/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:06:55 by francis           #+#    #+#             */
/*   Updated: 2025/01/04 10:53:53 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Prints all arguments of a command
 *
 * @param cmd Command structure containing arguments array
 */
void	ft_print_args(t_command *cmd)
{
	int	i;

	i = -1;
	printf("ft_print_args:\n");
	if (cmd && cmd->args)
	{
		while (cmd->args[++i])
			printf(" – arg[%d]: {%s} ", i, cmd->args[i]);
	}
	return ;
}

/**
 * @brief Converts redirection type to string representation
 *
 * @param redir_type Integer representing redirection type
 * @return char* String representation of redirection type
 */
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

/**
 * @brief Prints redirections for a specific command
 *
 * @param redir Redirection list to print
 * @param cmd_name Name of command for context
 */
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

/**
 * @brief Prints all redirections for all commands
 *
 * @param cmd Command list containing redirections
 */
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

/**
 * @brief Prints complete command sequences with args and redirections
 *
 * @param cmd Command list to print
 */
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
