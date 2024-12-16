/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:28:35 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/16 17:24:48 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	free(s1);
	return (result);
}

void	extract_var_name(char *arg, int *j, char *var_name)
{
	int	k;

	k = 0;
	(*j)++;
	if (arg[*j] == '?')
	{
		var_name[k++] = '?';
		var_name[k] = '\0';
		return ;
	}
	while (arg[*j] && (ft_isalnum(arg[*j]) || arg[*j] == '_'))
		var_name[k++] = arg[(*j)++];
	var_name[k] = '\0';
	(*j)--;
}

char	*convert_exit_status(int status)
{
	char	*result;

	result = ft_itoa(status);
	if (!result)
		return (ft_strdup("0"));
	return (result);
}

char	*expand_variable(char *new_arg,
	t_shell_state *shell_state, char *var_name)
{
	char	*env_value;
	char	*result;

	if (ft_strcmp(var_name, "?") == 0)
	{
		env_value = convert_exit_status(shell_state->last_exit_status);
		result = ft_strjoin_free(new_arg, env_value);
		free(env_value);
		return (result);
	}
	env_value = get_env_var(shell_state->envp, var_name);
	if (env_value)
		return (ft_strjoin_free(new_arg, env_value));
	return (new_arg);
}

char	*process_single_arg(t_cmd_args *arg_node,  t_shell_state *shell_state)
{
	char		*new_arg;
	char		var_name[256];
	char		tmp[2];
	int			j;
	t_expand	*expand_iter;

	new_arg = ft_strdup("");
	j = 0;
	expand_iter = arg_node->to_expand;
	while (arg_node->arg_string[j])
	{
		if (expand_iter && arg_node->arg_string[j] == '$')
		{
			if (expand_iter->check)
			{
				extract_var_name(arg_node->arg_string, &j, var_name);
				new_arg = expand_variable(new_arg, shell_state, var_name);
			}
			else
			{
				tmp[0] = arg_node->arg_string[j];
				tmp[1] = '\0';
				new_arg = ft_strjoin_free(new_arg, tmp);
			}
			expand_iter = expand_iter->next;
		}
		else
		{
			tmp[0] = arg_node->arg_string[j];
			tmp[1] = '\0';
			new_arg = ft_strjoin_free(new_arg, tmp);
		}
		j++;
	}
	return (new_arg);
}

void	fill_table(t_command *cmd_list, t_shell_state *shell_state)
{
	int			i;
	char		*new_arg;
	t_cmd_args	*current;
	t_command	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		i = 0;
		current = cmd->arg_list;
		while (current)
		{
			new_arg = process_single_arg(current, shell_state);
			free(current->arg_string);
			current->arg_string = new_arg;
			if (i == 0)
				cmd->cmd_name = current->arg_string;
			current = current->next;
			i++;
		}
		cmd = cmd->next;
	}
}

// arg_string=$USER => "hello, world !" => args[7]="hello, world !"
// => args[7]="hello,", args[8]="world", args[9]="!"

void	expand_command_variables(t_command *cmd_list,
	t_shell_state *shell_state)
{
	if (!cmd_list)
		return ;
	if (!cmd_list->arg_list || !cmd_list->arg_list->arg_string)
		return ;
/* 	if (cmd_list->redir_list && cmd_list->redir_list->heredoc)
		fill_table_heredocs(cmd_list, shell_state); */
	fill_table(cmd_list, shell_state);
	ft_allocate_cmd_args_to_array(cmd_list); // fonction à réviser
}
