/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:18:48 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 10:23:20 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

struct s_token	*ft_parse_operators(struct s_token *head)
{
	struct s_token	*iterator;

	iterator = head;
	while (iterator)
	{
		if (!(iterator->type))
		{
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

static struct s_command	*init_command(void)
{
	struct s_command	*cmd;

	cmd = malloc(sizeof(struct s_command));
	if (!cmd)
		return (NULL);
	cmd->cmd_name = NULL;
	cmd->args = NULL;
	return (cmd);
}

static char	**allocate_and_fill_args(struct s_token *head, int *arg_count)
{
	char	**args_array;
	int		i;

	args_array = malloc(sizeof(char *) * (*arg_count + 1));
	if (!args_array)
		return (NULL);
	i = 0;
	while (head)
	{
		if (head->type == WORD)
		{
			args_array[i] = ft_strdup(head->str);
			if (args_array[i] == NULL)
				return (NULL);
			i++;
		}
		head = head->next;
	}
	args_array[i] = NULL;
	return (args_array);
}

struct s_command	*ft_parse(struct s_token *head)
{
	struct s_command	*cmd_sequence;
	int					arg_count;
	struct s_token		*current;

	cmd_sequence = init_command();
	if (!cmd_sequence)
		return (NULL);
	arg_count = 0;
	if (head->type == WORD)
	{
		cmd_sequence->cmd_name = ft_strdup(head->str);
		head = head->next;
		current = head;
		while (current)
		{
			if (current->type == WORD)
				arg_count++;
			current = current->next;
		}
		cmd_sequence->args = allocate_and_fill_args(head, &arg_count);
		if (!cmd_sequence->args)
			return (NULL);
	}
	return (cmd_sequence);
}
