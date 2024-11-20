/* ************************************************************************** */
/*	                                                                    */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:35:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/15 20:18:47 by cmegret          ###   ########.fr       */
/*   Updated: 2024/11/01 13:18:40 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// probably not necessary, likely done before 
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

// Initializes our cmd_sequence (everything to NULL except input, output)
void	ft_initialize_cmd_sequence(t_command *cmd_sequence)
{
	cmd_sequence->cmd_name = NULL;
	cmd_sequence->args = NULL;
	cmd_sequence->arg_list = NULL;
	cmd_sequence->input = STDIN;
	cmd_sequence->output = STDOUT;
	cmd_sequence->redir_list = NULL;
	cmd_sequence->next = NULL;
}

void	ft_print_args(t_command *cmd_sequence)
{
	int	i;

	i = -1;
	printf("ft_print_args:\n");
	if (cmd_sequence && cmd_sequence->args)
	{
		while (cmd_sequence->args[++i])
			printf("arg[%d]: [%s]\n", i, cmd_sequence->args[i]);
	}
	return ;
}

// Parses our linked list of tokens, starting from left (head)
// Extracts the command and the arguments 
// Outputs a struct command with the command name and the arguments
t_command	*ft_parse(t_token *tok)
{
	t_command	*cmd_sequence;
	t_redir		*redir_list = NULL;

	cmd_sequence = malloc(sizeof(t_command)); // malloc a node to our list of commands (cmd_sequence)
	if (!cmd_sequence)
		return (NULL);
	ft_initialize_cmd_sequence(cmd_sequence);
	ft_parse_operators(tok);
	while (tok)
	{
		if (ft_token_is_redir(tok->type))
			ft_add_redir(&tok, redir_list); // add redirections to our redirections list
		else if (ft_token_is_word(tok->type))
			ft_add_cmd_arg(tok->str, cmd_sequence); // add WORD tokens to argument list
		tok = tok->next;
	}
	if (ft_allocate_args(cmd_sequence, cmd_sequence->arg_list) == -1)
		return (NULL);
	cmd_sequence->redir_list = redir_list;
	ft_print_args(cmd_sequence);
	return (cmd_sequence);
}

/* TO ADD: EXPAND_EXIT_STATUS: see this codxe from cmegret:
static int	ft_allocate_single_arg(t_token *tkn, t_command *cmd_sequence,
	t_shell_state *shell_state)
{
	cmd_sequence->args = malloc(2 * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1); // call error function ?
	cmd_sequence->args[0] = expand_exit_status(tkn->str, shell_state->last_exit_status);
	if (!cmd_sequence->args[0])
		return (-1);
	cmd_sequence->args[1] = NULL;
	cmd_sequence->next = NULL; // A CHANGER
	return (0);
}

static int	ft_allocate_multiple_args(t_token *tkn, t_command *cmd_sequence, int arg_count, t_shell_state *shell_state)
{
	int	i;

	cmd_sequence->args = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1);
	cmd_sequence->args[0] = ft_strdup(tkn->str);
	if (!cmd_sequence->args[0])
		return (-1);

	tkn = tkn->next;
	i = 1;
	while (tkn)
	{
		if (tkn->type == WORD)
		{
			cmd_sequence->args[i] = expand_exit_status(tkn->str,
					shell_state->last_exit_status);
			if (!cmd_sequence->args[i])
				return (-1);
			i++;
		}
		tkn = tkn->next;
	}
	cmd_sequence->args[i] = NULL;
	cmd_sequence->next = NULL;
	return (0);
}

static int	ft_process_args(t_token *tkn, t_command *cmd_sequence,
	t_shell_state *shell_state)
{
	int	arg_count;

	arg_count = ft_count_token_list_args(tkn);
	if (arg_count == 1)
	{
		if (ft_allocate_single_arg(tkn, cmd_sequence, shell_state) == -1)
			return (-1);
	}
	else
	{
		if (ft_allocate_multiple_args(tkn, cmd_sequence,
				arg_count, shell_state) == -1)
			return (-1);
	}
	return (0);
}
*/