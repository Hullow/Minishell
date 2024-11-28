/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:26:12 by fallan            #+#    #+#             */
/*   Updated: 2024/11/22 19:43:34 by francis          ###   ########.fr       */
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

// add a command argument: either cmd_name if no cmd_name yet
// or a command argument to our linked list of command arguments
int	ft_add_cmd_arg(char *tok_str, t_command *cmd_seq) // before: cmd_seq->cmd_name = strdup(tok->str);
{
	t_cmd_args	*head;

	if (!cmd_seq->cmd_name) // no command name
		cmd_seq->cmd_name = ft_strdup(tok_str); // malloc and add the command name
	else
	{
		if (!(cmd_seq->arg_list)) // if no argument list yet, malloc the argument list
		{
			cmd_seq->arg_list = malloc (sizeof(t_cmd_args));
			head = cmd_seq->arg_list;
		}
		else
		{
			head = cmd_seq->arg_list;
			while (cmd_seq->arg_list->next) // go to the penultimate element of the argument list
				cmd_seq->arg_list = cmd_seq->arg_list->next;
			cmd_seq->arg_list->next = malloc (sizeof(t_cmd_args)); // malloc a new argument node at the end of the list
			cmd_seq->arg_list = cmd_seq->arg_list->next;
		}
		if (!(cmd_seq->arg_list)) // malloc check
			return (-1);
		cmd_seq->arg_list->arg_string = ft_strdup(tok_str); // malloc and add the command argument
		if (!(cmd_seq->arg_list->arg_string))
				return (-1);
		cmd_seq->arg_list->next = NULL;
		cmd_seq->arg_list = head;
	}
	if (!(cmd_seq->cmd_name))
		return (-1);
	return (0);
}

// copies the command arguments from the argument linked list to the array of arguments
// free the linked list of command arguments
// do this over all commands (pipes)
int	ft_allocate_args(t_command *cmd_sequence)
{
	int	arg_count;
	int	i;

	while (cmd_sequence && cmd_sequence->cmd_name)
	{
		arg_count = ft_count_args(cmd_sequence->arg_list);
		cmd_sequence->args = malloc((arg_count + 2) * sizeof(char *));
		if (!cmd_sequence->args)
			return (-1);
		cmd_sequence->args[0] = ft_strdup(cmd_sequence->cmd_name);
		i = 0;
		while (cmd_sequence->arg_list && i < arg_count)
		{
			cmd_sequence->args[i + 1] = ft_strdup(cmd_sequence->arg_list->arg_string);
			if (cmd_sequence->args[i + 1] == NULL)
				return (-1);
			i++;
			cmd_sequence->arg_list = cmd_sequence->arg_list->next;
		}
		cmd_sequence->args[i + 1] = NULL;
		ft_free_arg_list(cmd_sequence->arg_list);
		cmd_sequence = cmd_sequence->next;
	}
	return (0);
}
