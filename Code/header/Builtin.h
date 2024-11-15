/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:38:32 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/14 15:55:59 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "Minishell.h"

typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

int			ft_is_builtin(char *cmd_name);
int			ft_execute_builtin(t_command *cmd, t_shell_state *shell_state);

// Builtin cdﬁﬁ
void		ft_cd(t_command *cmd, t_shell_state *shell_state);

// Builtin env
void		ft_env(t_shell_state *shell_state);
void		update_env_var(char ***envp, char *key, const char *value);

// Builtin export
void		ft_export(t_shell_state *shell_state, char **args);
const char	*extract_value(const char *new_value);
char		*build_new_var(const char *name, const char *value);
int			find_var_index(char **envp, char *name, size_t name_len);
int			update_existing_var(char ***envp, char *name,
				const char *new_value);
void		add_new_var(char ***envp, const char *var);
char		*get_var_name(const char *var);
int			is_valid_name(const char *name);

// Builtin unset
void		ft_unset(t_shell_state *shell_state, char **args);

// Builtin pwd
void		ft_pwd(t_shell_state *shell_state);

// Builtin echo
void		ft_echo(char **args, t_shell_state *shell_state);

// Builtin exit
void		ft_exit(t_shell_state *shell_state, char **args);

#endif