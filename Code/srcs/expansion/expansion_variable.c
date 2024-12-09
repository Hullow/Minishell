/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/09 14:54:15 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

char	*expand_variables(char *str, t_shell_state *state)
{
	char	*result;
	char	*tmp;
	int		i;
	int		in_quotes;
	int		in_dquotes;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	in_quotes = 0;
	in_dquotes = 0;
	while (str[i])
	{
		tmp = handle_quotes(str, &i, &in_quotes, &in_dquotes);
		if (!tmp && str[i] == '$' && !in_quotes)
			tmp = handle_expansion(str, &i, state);
		if (!tmp)
			tmp = ft_chartostr(str[i++]);
		result = ft_strjoin_free(result, tmp);
		free(tmp);
	}
	return (result);
}

void	expand_command_variables(t_command *cmd_list, t_shell_state *shell_state)
{
	t_command	*current;
	t_redir		*redir;
	int			i;

	current = cmd_list;
	i = 0;
	while (current)
	{
		if (current->cmd_name)
			current->cmd_name
				= expand_variables(current->cmd_name, shell_state);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				current->args[i]
					= expand_variables(current->args[i], shell_state);
				i++;
			}
		}
		redir = current->redir_list;
		while (redir)
		{
			if (redir->str)
				redir->str = expand_variables(redir->str, shell_state);
			redir = redir->next;
		}
		current = current->next;
	}
}
