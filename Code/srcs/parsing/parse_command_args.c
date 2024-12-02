/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:26:12 by fallan            #+#    #+#             */
/*   Updated: 2024/12/02 18:16:11 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// returns the number of arguments in our argument list
int	ft_count_args(t_cmd_args *arg_list)
{
	int	i;

	i = 0;
	if (!arg_list)
		return (0);
	while (arg_list)
	{
		i++;
		arg_list = arg_list->next;
	}
	return (i);
}

// frees our linked list of arguments
void	ft_free_arg_list(t_cmd_args	*arg_list)
{
	t_cmd_args	*temp = NULL;

	while (arg_list)
	{
		temp = arg_list;
		if (arg_list->arg_string)
			free(arg_list->arg_string);
		arg_list = arg_list->next;
		free(temp);
	}
}

// add a command argument to our linked list of command arguments
// if no argument, malloc the first argument
// else, go to the end of the list and malloc an additional argument
int	ft_new_cmd_arg_node(t_cmd_args *arg_list, char *arg_string)
{
	if (!arg_list)
	{
		arg_list = malloc (sizeof(t_cmd_args));
		if (!arg_list)
			return (-1);
	}
	else
	{
		while (arg_list->next)
			arg_list = arg_list->next;
		arg_list->next = malloc (sizeof(t_cmd_args));
		if (!arg_list->next)
			return (-1);
		arg_list = arg_list->next;
	}
	arg_list->arg_string = ft_strdup(arg_string);
	arg_list->next = NULL;
	return (0);
}

// adds a command name or command argument:
// IF no cmd_name => add cmd_name
// ELSE => add a command argument to arg_list (our linked list of command arguments)
// N.b.: head is initialized to NULL by the calling function
int	ft_add_cmd_arg_to_list(char *tok_str, t_command *cmd_seq)
{
	t_cmd_args *head;

	if (!(cmd_seq->arg_list)) // if no argument list, malloc one
	{
		cmd_seq->arg_list = malloc (sizeof(t_cmd_args));
		cmd_seq->arg_list->next = NULL;
		head = cmd_seq->arg_list;
	}
	else // go to the end of the argument list
	{
		head = cmd_seq->arg_list;
		while (cmd_seq->arg_list->next) // go to the penultimate element of the argument list
			cmd_seq->arg_list = cmd_seq->arg_list->next;
		cmd_seq->arg_list->next = malloc (sizeof(t_cmd_args)); // malloc a new argument node at the end of the list
		cmd_seq->arg_list = cmd_seq->arg_list->next;
	}
	if (!(cmd_seq->arg_list)) // malloc check
		return (-1);
	cmd_seq->arg_list->arg_string = ft_strdup(tok_str); // ADDING THE STRING
	if (!(cmd_seq->arg_list->arg_string))
			return (-1);
	cmd_seq->arg_list->next = NULL;
	cmd_seq->arg_list = head;
	return (0);
}

// copies the command arguments from the argument linked list to the array of arguments
// free the linked list of command arguments
// do this for each command (each pipe)
int	ft_allocate_cmd_args_to_array(t_command *cmd_sequence)
{
	int			arg_count;
	int			i;
	t_cmd_args	*arg_iterator;

	printf("ft_allocate_cmd_args_to_array\n");
	while (cmd_sequence)
	{
		printf("segfault check 3.5\n");
		if (cmd_sequence->arg_list)
			arg_iterator = cmd_sequence->arg_list;
		else
			return (1);
		arg_count = ft_count_args(cmd_sequence->arg_list);
		printf("arg count: %d\n", arg_count);
		cmd_sequence->args = malloc((arg_count + 1) * sizeof(char *));
		if (!cmd_sequence->args)
			return (-1);
		i = 0;
		while (arg_iterator && i < arg_count)
		{
			cmd_sequence->args[i] = ft_strdup(arg_iterator->arg_string);
			printf("allocating {%s} to args[%d]\n", arg_iterator->arg_string, i);
			if (cmd_sequence->args[i] == NULL)
				return (-1);
			i++;
			arg_iterator = arg_iterator->next;
		}
		cmd_sequence->args[i] = NULL;
		printf("segfault check 1\n");
		ft_free_arg_list(cmd_sequence->arg_list);
		printf("segfault check 2\n");
		cmd_sequence = cmd_sequence->next;
		printf("segfault check 3\n");
	}
	if (cmd_sequence->args)
	{
		printf("segfault check 4\n");
		cmd_sequence->cmd_name = cmd_sequence->args[0];
		printf("segfault check 5\n");
	}
	printf("segfault check 6\n");
	return (0);
}
