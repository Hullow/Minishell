/* 
#include "../../header/Minishell.h"

char	*process_redir_str(char *str,
	t_shell_state *shell_state, int *word_count, int j)
{
	char		*expanded_str;
	char		**temp_table;
	t_params	params;

	temp_table = NULL;
	if (!str)
		return (NULL);
	while (str[j])
	{
		params.arg = str;
		params.j = &j;
		temp_table = malloc(sizeof(char *)
				* (count_words_in_arg(str, shell_state) + 1));
		params.table = temp_table;
		params.word_count = word_count;
		if (str[j] == '$')
		{
			process_variable(&params, shell_state);
			expanded_str = ft_strjoin(ft_strdup(""), temp_table[0]);
			ft_free_array(temp_table);
		}
		else
			j++;
	}
	return (expanded_str);
}

void	expand_redir_variables(t_redir *redir_list, t_shell_state *shell_state)
{
	char	*expanded_str;
	int		word_count;

	word_count = 0;
	while (redir_list)
	{
		expanded_str
			= process_redir_str(redir_list->str, shell_state, &word_count, 0);
		if (expanded_str)
		{
			free(redir_list->str);
			redir_list->str = expanded_str;
		}
		redir_list = redir_list->next;
	}
}

int	expand_env_variable(char *var, char **table,
	int *word_count, t_shell_state *shell_state)
{
	char	*env_value;
	char	**split_env;
	int		k;

	k = 0;
	env_value = get_env_var(shell_state->envp, var);
	if (env_value)
	{
		split_env = ft_split(env_value, ' ');
		while (split_env[k])
		{
			table[*word_count] = ft_strdup(split_env[k]);
			(*word_count)++;
			k++;
		}
		ft_free_array(split_env);
	}
	return (k);
}

int	process_variable(t_params *params, t_shell_state *shell_state)
{
	int	count;

	count = 0;
	if (params->arg[*(params->j) + 1] == '?')
	{
		params->table[*(params->word_count)]
			= ft_itoa(shell_state->last_exit_status);
		(*(params->word_count))++;
		*(params->j) += 2;
		count++;
	}
	else
	{
		count += expand_env_variable(&params->arg[*(params->j) + 1],
				params->table, params->word_count, shell_state);
		(*(params->j))++;
		while (params->arg[*(params->j)]
			&& !ft_isspace(params->arg[*(params->j)]))
			(*(params->j))++;
	}
	return (count);
}

int	process_non_variable(t_params *params)
{
	int		start;
	char	*word;

	start = *(params->j);
	while (params->arg[*(params->j)] && params->arg[*(params->j)] != '$')
		(*(params->j))++;
	word = ft_substr(params->arg, start, *(params->j) - start);
	if (word)
	{
		params->table[*(params->word_count)] = word;
		(*(params->word_count))++;
		return (1);
	}
	return (0);
}
 */