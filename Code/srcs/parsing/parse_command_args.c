/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:26:12 by fallan            #+#    #+#             */
/*   Updated: 2024/12/16 16:48:14 by francis          ###   ########.fr       */
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

// Fills up our linked list of command arguments:
// (t_cmd_args *: cmd_seq->arg_list)
// - if no argument list, malloc one
// - else:
// 		- go to the last argument of the argument list
// 		- malloc a new argument list node
//		- copy the string from our tokenized input to our argument list node
// N.b.: head is initialized to NULL by the calling function
int	ft_add_cmd_arg_to_list(t_token *tok, t_cmd_args **arg_list)
{
	t_cmd_args	*head;

	if (!((*arg_list)))
	{
		(*arg_list) = malloc (sizeof(t_cmd_args));
		(*arg_list)->next = NULL;
		head = (*arg_list);
	}
	else
	{
		head = (*arg_list);
		while ((*arg_list)->next)
			(*arg_list) = (*arg_list)->next;
		(*arg_list)->next = malloc (sizeof(t_cmd_args));
		(*arg_list) = (*arg_list)->next;
	}
	if (!((*arg_list)))
		return (-1);
	(*arg_list)->arg_string = ft_strdup(tok->str);
	if (tok->to_expand)
		(*arg_list)->to_expand = tok->to_expand;
	if (!((*arg_list)->arg_string))
		return (-1);
	(*arg_list)->next = NULL;
	(*arg_list) = head;
	return (0);
}

// copies arguments from:
// 		- the argument linked list (t_cmd_args *: cmd->arg_list)
// to:
// 		- the argument array (char **: cmd->args)
int	ft_copy_command_args(t_command *cmd, int arg_count)
{
	int			i;
	t_cmd_args	*arg_iterator;

	i = 0;
	arg_iterator = cmd->arg_list;
	while (arg_iterator && i < arg_count)
	{
		cmd->args[i] = ft_strdup(arg_iterator->arg_string);
		if (cmd->args[i] == NULL)
			return (-1);
		arg_iterator = arg_iterator->next;
		i++;
	}
	return (i);
}

// - if there is a list of arguments (cmd_list_>arg_list),
// 		calls ft_count_args to count them (else: returns 1),
// - mallocs an array of command arguments of that size,
// - calls ft_copy_command_args to copies the arguments from 
// 		the argument linked list to the argument array it just created
// - calls ft_free_arg_list to free the linked list of command arguments
// - does this for each command (each pipe)
int	ft_allocate_cmd_args_to_array(t_command *cmd)
{
	int			arg_count;
	int			i;

	while (cmd)
	{
		if (!(cmd->arg_list))
			return (1);
		arg_count = ft_count_args(cmd->arg_list);
		cmd->args = malloc((arg_count + 1) * sizeof(char *));
		i = ft_copy_command_args(cmd, arg_count);
		cmd->args[i] = NULL;
		cmd->cmd_name = cmd->args[0];
		cmd = cmd->next;
	}
	return (0);
}
