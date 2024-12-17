/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:41:45 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/17 15:54:47 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

char	*process_single_arg(t_cmd_args *arg_node, t_shell_state *shell_state)
{
	char		*new_arg;
	int			i;
	t_expand	*expand_iter;

	new_arg = ft_strdup("");
	i = 0;
	expand_iter = arg_node->to_expand;
	while (arg_node->arg_string[i])
	{
		if (arg_node->arg_string[i] == '$' && expand_iter)
		{
			if (expand_iter->check)
				new_arg = handle_variable_expansion(new_arg, shell_state,
						arg_node->arg_string, &i);
			else
				new_arg = append_single_char(new_arg, arg_node->arg_string[i]);
			expand_iter = expand_iter->next;
		}
		else
			new_arg = append_single_char(new_arg, arg_node->arg_string[i]);
		i++;
	}
	return (new_arg);
}

char	*process_heredoc_line(char *line, t_shell_state *shell_state)
{
	char	*new_line;
	char	var_name[256];
	char	tmp[2];
	int		j;

	new_line = ft_strdup("");
	j = 0;
	while (line[j])
	{
		if (line[j] == '$')
		{
			extract_var_name(line, &j, var_name);
			new_line = expand_variable(new_line, shell_state, var_name);
		}
		else
		{
			tmp[0] = line[j];
			tmp[1] = '\0';
			new_line = ft_strjoin_free(new_line, tmp);
		}
		j++;
	}
	return (new_line);
}
