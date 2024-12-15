/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:57 by francis           #+#    #+#             */
/*   Updated: 2024/12/14 11:38:27 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "Minishell.h"

typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Execution
int		execute_cmd(t_command *cmd_list, t_shell_state *shell_state);
pid_t	execute_pipeline(t_command *cmd_list, t_shell_state *shell_state,
			int in_fd, int *next_in_fd);
void	execute_child(t_command *cmd_list,
			t_shell_state *shell_state, int in_fd, int *fd);
void	handle_parent(int in_fd, int *fd);
int		handle_parent_builtin(t_command *cmd_list, t_shell_state *shell_state);
void	ft_execute_builtin(t_command *cmd, t_shell_state *shell_state);
int		ft_is_builtin(char *cmd_name);
char	**get_env_paths(char **envp);
char	*get_cmd_path(char *cmd, char **envp);
void	handle_child_process(t_command *cmd_list, t_shell_state *shell_state);
char	*resolve_cmd_path(char *cmd_name, t_shell_state *shell_state);
void	check_access_rights(char *cmd_path, char *cmd_name,
			t_shell_state *shell_state);
void	configure_redirections(t_command *cmd, t_shell_state *shell_state);
void	restore_redirections(t_command *cmd_list);
void	wait_for_pipeline(pid_t *pipeline_pids, int pid_count,
			t_shell_state *shell_state);
void	setup_file_descriptors(t_command *cmd_list, int in_fd, int *fd);
void	run_command(t_command *cmd_list, t_shell_state *shell_state);
int		is_valid_filename(const char *filename);
bool	has_heredoc(t_command *cmd);
int		setup_heredoc_input(t_command *cmd);

#endif