/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:26:12 by fallan            #+#    #+#             */
/*   Updated: 2024/12/07 14:34:55 by francis          ###   ########.fr       */
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
	t_cmd_args	*temp;

	temp = NULL;
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
// ELSE 
// => add a command argument to arg_list (our linked list of command arguments)
// N.b.: head is initialized to NULL by the calling function
int	ft_add_cmd_arg_to_list(char *tok_str, t_command *cmd_seq)
{
	t_cmd_args	*head;

	if (!(cmd_seq->arg_list)) // if no argument list, malloc one
	{
		cmd_seq->arg_list = malloc (sizeof(t_cmd_args));
		cmd_seq->arg_list->next = NULL;
		head = cmd_seq->arg_list;
	}
	else // go to the end of the argument list
	{
		head = cmd_seq->arg_list;
		// go to the penultimate element of the argument list
		while (cmd_seq->arg_list->next)
			cmd_seq->arg_list = cmd_seq->arg_list->next;
		// malloc a new argument node at the end of the list
		cmd_seq->arg_list->next = malloc (sizeof(t_cmd_args));
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

// copies arguments
/* int	ft_copy_command_args(t_command *cmd_list, t_cmd_args *arg_iterator, int arg_count)
{
	int	i;

	i = 0;
	while (arg_iterator && i < arg_count)
	{
		cmd_list->args[i] = ft_strdup(arg_iterator->arg_string);
		if (cmd_list->args[i] == NULL)
			return (-1);
		arg_iterator = arg_iterator->next;
		i++;
	}
	return (i);
} */

// - copies the command arguments from 
// 		the argument linked list to the array of arguments
// - frees the linked list of command arguments
// - does this for each command (each pipe)
int	ft_allocate_cmd_args_to_array(t_command *cmd_list)
{
	int			arg_count;
	int			i;
	t_cmd_args	*arg_iterator;

	while (cmd_list)
	{
		if (cmd_list->arg_list)
			arg_iterator = cmd_list->arg_list;
		else
			return (1);
		arg_count = ft_count_args(cmd_list->arg_list);
		cmd_list->args = malloc((arg_count + 1) * sizeof(char *));
		if (!cmd_list->args)
			return (-1);
		// i = ft_copy_command_args(cmd_list, arg_iterator, arg_count);
		i = 0;
		while (arg_iterator && i < arg_count)
		{
			cmd_list->args[i] = ft_strdup(arg_iterator->arg_string);
			if (cmd_list->args[i] == NULL)
				return (-1);
			arg_iterator = arg_iterator->next;
			i++;
		}
		cmd_list->args[i] = NULL;
		cmd_list->cmd_name = cmd_list->args[0];
		ft_free_arg_list(cmd_list->arg_list);
		cmd_list = cmd_list->next;
	}
	return (0);
}
