/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:38:32 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/07 12:02:15 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "Minishell.h"

typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Builtin cdﬁﬁ
void		ft_cd(t_command *cmd);
int			ft_execute_cd(t_command *cmd);

// Builtin env
void		ft_env(char **envp);
int			ft_execute_env(t_command *cmd, t_shell_state *shell_state);

// Builtin export
int			ft_execute_export(t_command *cmd, t_shell_state *shell_state);
void		ft_export(char ***envp, char **args);
const char	*extract_value(const char *new_value);
char		*build_new_var(const char *name, const char *value);
int			find_var_index(char **envp, char *name, size_t name_len);
int			update_existing_var(char ***envp, char *name,
				const char *new_value);
void		add_new_var(char ***envp, const char *var);
char		*get_var_name(const char *var);
int			is_valid_name(const char *name);

// Builtin unset
void		ft_unset(char ***envp, char **args);
int			ft_execute_unset(t_command *cmd, t_shell_state *shell_state);

// Builtin pwd
void		ft_pwd(void);
int			ft_execute_pwd(t_command *cmd);

// Builtin echo
int			ft_execute_echo(t_command *cmd);
void		ft_echo(char **args);

// Builtin exit
void		ft_exit(char ***envp, t_shell_state *shell_state);
int			ft_execute_exit(t_command *cmd, t_shell_state *shell_state);

#endif