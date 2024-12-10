/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:38 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/10 18:06:37 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "Minishell.h"

typedef struct s_params	t_params;
typedef struct s_redir	t_redir;

void	expand_command_variables(t_command *cmd_list,
			t_shell_state *shell_state);
void	fill_table(t_command *cmd_list,
			t_shell_state *shell_state);
int		count_total_words(t_command *cmd_list, t_shell_state *shell_state);
int		count_words_in_arg(char *arg, t_shell_state *shell_state);
int		count_variable_words(char *arg, int *j, t_shell_state *shell_state);
int		count_non_variable_words(char *arg, int *j);
int		count_env_variable_words(char *var, t_shell_state *shell_state);
void	ft_free_array(char **array);
char	*ft_extract_word(char *str, int *index);
int		expand_env_variable(char *var, char **table, int *word_count,
			t_shell_state *shell_state);
int		process_variable(t_params *params,
			t_shell_state *shell_state);
int		process_non_variable(t_params *params);
void	expand_redir_variables(t_redir *redir_list,
			t_shell_state *shell_state);
char	*process_redir_str(char *str,
			t_shell_state *shell_state, int *word_count);

#endif