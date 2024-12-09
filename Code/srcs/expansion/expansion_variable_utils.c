/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:41:17 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/09 15:36:48 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/* char	*get_expansion_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	name = ft_substr(str, 0, i);
	return (name);
}

char	*ft_chartostr(char c)
{
	char	*str;

	str = (char *)malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	char	*old_s1;

	if (!s1 || !s2)
		return (NULL);
	old_s1 = s1;
	result = ft_strjoin(s1, s2);
	free(old_s1);
	return (result);
}

char	*handle_quotes(char *str, int *i, int *in_quotes, int *in_dquotes)
{
	if (str[*i] == '\'')
	{
		if (!*in_dquotes)
			*in_quotes = !*in_quotes;
		return (ft_chartostr(str[(*i)++]));
	}
	else if (str[*i] == '\"')
	{
		*in_dquotes = !*in_dquotes;
		return (ft_chartostr(str[(*i)++]));
	}
	return (NULL);
}

char	*handle_expansion(char *str, int *i, t_shell_state *state)
{
	char	*tmp;
	char	*var_name;
	char	*env_value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(state->last_exit_status));
	}
	if (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		var_name = get_expansion_var_name(&str[*i]);
		env_value = getenv(var_name);
		*i += ft_strlen(var_name);
		if (env_value)
			tmp = ft_strdup(env_value);
		else
			tmp = ft_strdup("");
		free(var_name);
		return (tmp);
	}
	return (ft_strdup("$"));
} */
