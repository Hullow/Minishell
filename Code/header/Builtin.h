/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/24 02:44:39 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "Minishell.h"

// Errors for Exit
# define NUMERIC_ARG_REQUIRED		0
# define TOO_MANY_ARGUMENTS			1

typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Builtin CD
void		ft_cd(t_command *cmd, t_shell_state *shell_state);
char		*get_env_var(char **envp, char *key);
void		update_env_var(char ***envp, char *name, const char *value);

// Builtin ECHO
void		ft_echo(char **args, t_shell_state *shell_state);

// Builtin ENV
void		ft_env(t_shell_state *shell_state);
int			update_existing_var(char ***envp,
				char *name, const char *new_value);
char		*build_new_var(const char *name, const char *value);
const char	*extract_value(const char *new_value);
void		add_new_env_var(char ***envp, char *new_var);
void		copy_env_vars(char **new_envp, char **envp, int count);
int			find_var_index(char **envp, char *key, size_t key_len);
void		add_new_var(char ***envp, const char *var);

// Builtin EXIT
void		ft_exit(t_shell_state *shell_state, char **args, int exit_stat, \
				int i);

// Builtin EXPORT
void		ft_export(t_shell_state *shell_state, char **args);
char		*get_var_name(const char *var);
int			is_valid_name(const char *name);

// Builtin PWD
void		ft_pwd(t_shell_state *shell_state);

// Builtin UNSET
void		ft_unset(t_shell_state *shell_state, char **args);
void		remove_var(char ***envp, int index);

#endif