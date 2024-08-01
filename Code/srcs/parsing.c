/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:26:30 by francis           #+#    #+#             */
/*   Updated: 2024/08/01 15:18:43 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

struct command	*ft_parse(struct token *head)
{
	struct command	*cmd;
	char			**args_array;
	int				i;

	cmd = malloc (sizeof(struct command));
	if (!cmd)
		return (NULL);
	args_array = NULL;
	i = 0;
	if (head->type == WORD)
	{
		cmd->cmd_name = ft_strdup(head->str);
		head = head->next;
		if (head)
			args_array = malloc(sizeof(char **)); // CHECK MALLOC
		while (head)
		{
			if (head->type == WORD)
			{
				args_array[i] = ft_strdup(head->str);
				if (args_array[i] == NULL)
					return (NULL);
			}
			i++;
			head = head->next;
		}
		//args_array[i] = "";
		cmd->args = args_array;
	}
	return (cmd);
}