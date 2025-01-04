/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:26:12 by fallan            #+#    #+#             */
/*   Updated: 2025/01/04 10:52:54 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Counts the number of arguments in the argument list
 *
 * @param arg_list List of command arguments
 * @return int Number of arguments
 */
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

/**
 * @brief Adds a new command argument to the argument list
 *
 * @param tok Token containing the argument
 * @param arg_list Pointer to argument list
 * @param head Head of argument list
 * @return int 0 on success, -1 on failure
 */
int	ft_add_cmd_arg_to_list(t_token *tok, t_cmd_args **arg_list,
	t_cmd_args *head)
{
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

/**
 * @brief Copies command arguments from linked list to array
 *
 * @param cmd Command structure containing arguments
 * @param arg_count Number of arguments to copy
 * @return int Number of arguments copied, -1 on error
 */
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

/**
 * @brief Allocates and fills argument arrays for all commands
 *
 * @param cmd Command list to process
 * @return int 0 on success
 */
int	ft_allocate_cmd_args_to_array(t_command *cmd)
{
	int			arg_count;
	int			i;

	while (cmd)
	{
		if (!(cmd->arg_list))
		{
			cmd = cmd->next;
			continue ;
		}
		arg_count = ft_count_args(cmd->arg_list);
		cmd->args = malloc((arg_count + 1) * sizeof(char *));
		i = ft_copy_command_args(cmd, arg_count);
		cmd->args[i] = NULL;
		if (!(cmd->cmd_name))
			cmd->cmd_name = cmd->args[0];
		cmd = cmd->next;
	}
	return (0);
}
