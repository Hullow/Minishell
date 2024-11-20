/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:01:43 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/20 16:32:12 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

char	*expand_exit_status(char *arg, int last_exit_status)
{
	char	*exit_status_str;
	char	*part1;
	char	*result;
	char	*pos;

	pos = ft_strnstr(arg, "$?", ft_strlen(arg));
	if (pos == NULL)
		return (ft_strdup(arg));
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
