/* 
#include "../../header/Minishell.h"

int	count_env_variable_words(char *var, t_shell_state *shell_state)
{
	char	*env_value;
	char	**split_env;
	int		count;
	int		k;

	count = 0;
	k = 0;
	env_value = get_env_var(shell_state->envp, var);
	if (env_value)
	{
		split_env = ft_split(env_value, ' ');
		while (split_env[k])
		{
			count++;
			k++;
		}
		ft_free_array(split_env);
	}
	return (count);
}

int	count_variable_words(char *arg, int *j, t_shell_state *shell_state)
{
	int	word_count;

	word_count = 0;
	if (arg[*j + 1] == '?')
	{
		word_count++;
		*j += 2;
	}
	else
	{
		word_count += count_env_variable_words(&arg[*j + 1], shell_state);
		(*j)++;
		while (arg[*j] && !ft_isspace(arg[*j]))
			(*j)++;
	}
	return (word_count);
}

int	count_non_variable_words(char *arg, int *j)
{
	int	word_count;

	word_count = 1;
	while (arg[*j] && arg[*j] != '$')
		(*j)++;
	return (word_count);
}

int	count_words_in_arg(char *arg, t_shell_state *shell_state)
{
	int	j;
	int	word_count;

	j = 0;
	word_count = 0;
	while (arg[j])
	{
		if (arg[j] == '$')
			word_count += count_variable_words(arg, &j, shell_state);
		else
			word_count += count_non_variable_words(arg, &j);
	}
	return (word_count);
}

int	count_total_words(t_command *cmd_list, t_shell_state *shell_state)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (cmd_list->args[i])
	{
		word_count += count_words_in_arg(cmd_list->args[i], shell_state);
		i++;
	}
	return (word_count);
}
 */