/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:38 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/24 13:54:26 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "Minishell.h"

typedef struct s_params		t_params;
typedef struct s_redir		t_redir;
typedef struct s_cmd_args	t_cmd_args;
typedef struct s_expand		t_expand;

// Utils
char	*ft_strjoin_free(char *s1, char *s2);
void	extract_var_name(char *arg, int *j, char *var_name);
char	*convert_exit_status(int status);
char	*append_single_char(char *str, char c);
char	*handle_variable_expansion(char *new_arg, t_shell_state *shell_state,
			char *arg_string, int *i);

// Variable expansion
char	*expand_variable(char *new_arg,
			t_shell_state *shell_state, char *var_name);

// Process
char	*process_single_arg(char *str, t_expand *to_expand,
			t_shell_state *shell_state);
char	*process_heredoc_line(char *line, t_shell_state *shell_state);
void	process_command_redirections(t_command *cmd,
			t_shell_state *shell_state);
void	process_command_args(t_command *cmd,
			t_shell_state *shell_state);

// Main expansion functions
void	expand_command_variables(t_command *cmd_list,
			t_shell_state *shell_state);
void	fill_table(t_command *cmd_list, t_shell_state *shell_state);
void	fill_table_heredocs(t_command *cmd_list, t_shell_state *shell_state);

#endif