/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:38 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/03 07:40:33 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "Minishell.h"

typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Execution
int		execute_cmd(t_command *cmd_list, t_shell_state *shell_state);
int		execute_pipeline(t_command *cmd_list,
			t_shell_state *shell_state, int in_fd);
void	execute_child(t_command *cmd_list,
			t_shell_state *shell_state, int in_fd, int *fd);
void	handle_parent(pid_t pid, int in_fd, int *fd);
int		handle_parent_builtin(t_command *cmd_list, t_shell_state *shell_state);
void	ft_execute_builtin(t_command *cmd, t_shell_state *shell_state);
int		ft_is_builtin(char *cmd_name);
char	**get_env_paths(char **envp);
char	*get_cmd_path(char *cmd, char **envp);
void	handle_child_process(t_command *cmd_list, char **envp);
char	*resolve_cmd_path(char *cmd_name, char **envp);
void	check_access_rights(char *cmd_path, char *cmd_name);

#endif