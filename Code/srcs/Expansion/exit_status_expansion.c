/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:01:43 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/21 14:34:19 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// OLD CODE in parse_main.c
/*
static int	ft_allocate_multiple_args(t_token *tkn, t_command *cmd_sequence, int arg_count, t_shell_state *shell_state)
{
(....)
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
*/

// Called from parse_main.c
// Integrate this code in parameter_expansion.c
char	*expand_exit_status(char *arg, int last_exit_status)
{
	char	*exit_status_str;
	char	*part1;
	char	*result;
	char	*pos;

	pos = ft_strnstr(arg, "$?", ft_strlen(arg));
	if (pos == NULL)
		return (arg);
	exit_status_str = ft_itoa(last_exit_status);
	if (!exit_status_str)
		return (NULL);
	part1 = ft_strjoin(ft_substr(arg, 0, pos - arg), exit_status_str);
	free(exit_status_str);
	if (!part1)
		return (NULL);
	result = ft_strjoin(part1, pos + 2);
	free(part1);
	if (!result)
		return (NULL);
	return (result);
}
