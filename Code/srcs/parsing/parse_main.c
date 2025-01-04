/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:35:01 by francis           #+#    #+#             */
/*   Updated: 2025/01/04 10:55:01 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Assigns operator types to tokens based on their string content
 *
 * @param head Start of token list
 * @return t_token* Updated token list with operator types assigned
 */
t_token	*ft_parse_operators(t_token *head)
{
	t_token	*iterator;

	iterator = head;
	while (iterator)
	{
		if (!(iterator->type))
		{
			if (!iterator->str)
				return (head);
			if (!(ft_strncmp(iterator->str, ">", 2)))
				iterator->type = REDIR_OUTPUT;
			else if (!(ft_strncmp(iterator->str, "<", 2)))
				iterator->type = REDIR_INPUT;
			else if (!(ft_strncmp(iterator->str, ">>", 3)))
				iterator->type = REDIR_APPEND;
			else if (!(ft_strncmp(iterator->str, "<<", 3)))
				iterator->type = REDIR_HEREDOC;
			else if (!(ft_strncmp(iterator->str, "|", 2)))
				iterator->type = PIPE;
		}
		iterator = iterator->next;
	}
	return (head);
}

/**
 * @brief Initializes all fields of a command structure
 *
 * @param cmd_list Command structure to initialize
 */
void	ft_initialize_cmd_list(t_command *cmd_list)
{
	cmd_list->cmd_name = NULL;
	cmd_list->cmd_index = 1;
	cmd_list->args = NULL;
	cmd_list->arg_list = NULL;
	cmd_list->saved_input = STDIN;
	cmd_list->saved_output = STDOUT;
	cmd_list->redir_list = NULL;
	cmd_list->skip_execution = 0;
	cmd_list->next = NULL;
}

/**
 * @brief Creates and initializes a new command after a pipe
 *
 * @param cmd_list Current command structure
 * @return t_command* New command structure or NULL if allocation fails
 */
t_command	*ft_add_pipe(t_command *cmd_list)
{
	int	cmd_index;

	cmd_index = cmd_list->cmd_index;
	cmd_list->next = malloc(sizeof(t_command));
	if (!(cmd_list->next))
		return (NULL);
	cmd_list = cmd_list->next;
	ft_initialize_cmd_list(cmd_list);
	cmd_list->cmd_index = cmd_index + 1;
	return (cmd_list);
}

/**
 * @brief Validates redirection syntax in token list
 *
 * @param tokens Token list to validate
 * @return int 0 if valid, 2 if syntax error found
 */
int	validate_redirections(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == REDIR_OUTPUT
			|| current->type == REDIR_INPUT
			|| current->type == REDIR_APPEND
			|| current->type == REDIR_HEREDOC)
		{
			if (current->next && (current->next->type == REDIR_OUTPUT
					|| current->next->type == REDIR_INPUT
					|| current->next->type == REDIR_APPEND
					|| current->next->type == REDIR_HEREDOC))
			{
				ft_putstr_fd("minishell: syntax error ", 2);
				ft_putstr_fd("unexpected token `", 2);
				ft_putstr_fd(current->next->str, 2);
				ft_putstr_fd("'\n", 2);
				return (2);
			}
		}
		current = current->next;
	}
	return (0);
}

/**
 * @brief Main parsing function for command input
 *
 * @param tok Token list to parse
 * @param shell_state Current shell state
 * @return t_command* Parsed command list or NULL if error
 */
t_command	*ft_parse(t_token *tok, t_shell_state *shell_state)
{
	t_command	*cmd_list;
	t_command	*head_cmd;

	cmd_list = malloc(sizeof(t_command));
	if (!cmd_list)
		return (NULL);
	ft_initialize_cmd_list(cmd_list);
	head_cmd = cmd_list;
	ft_parse_operators(tok);
	if (validate_redirections(tok) != 0 || validate_pipes(tok, 0) != 0)
	{
		shell_state->last_exit_status = 2;
		return (NULL);
	}
	while (tok)
	{
		if (ft_token_is_redir(tok->type))
			ft_add_redir(&tok, cmd_list);
		else if (ft_token_is_word(tok->type))
			ft_add_cmd_arg_to_list(tok, &(cmd_list->arg_list), NULL);
		else if (ft_token_is_pipe(tok->type))
			cmd_list = ft_add_pipe(cmd_list);
		tok = tok->next;
	}
	return (head_cmd);
}
