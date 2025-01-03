/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:57 by francis           #+#    #+#             */
/*   Updated: 2025/01/03 00:18:45 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "Minishell.h"

/* Typedefs */
typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;
typedef struct s_redir			t_redir;

/* Exécution principale */
int		execute_cmd(t_command *cmd_list, t_shell_state *shell_state);
void	run_command(t_command *cmd_list, t_shell_state *shell_state);
int		ft_is_builtin(char *cmd_name);
void	ft_execute_builtin(t_command *cmd, t_shell_state *shell_state);

/* Gestion des processus */
pid_t	execute_pipeline(t_command *cmd_list, t_shell_state *shell_state,
			int in_fd, int *next_in_fd);
void	execute_child(t_command *cmd_list,
			t_shell_state *shell_state, int in_fd, int *fd);
void	handle_parent(int in_fd, int *fd);
int		handle_parent_builtin(t_command *cmd_list, t_shell_state *shell_state);
void	handle_child_process(t_command *cmd_list, t_shell_state *shell_state);
void	wait_for_pipeline(pid_t *pipeline_pids, int pid_count,
			t_shell_state *shell_state);
void	setup_file_descriptors(t_command *cmd_list, int in_fd, int *fd);

/* Gestion des chemins */
char	**get_env_paths(char **envp);
char	*get_cmd_path(char *cmd, char **envp, int i, char *temp);
char	*resolve_cmd_path(char *cmd_name, t_shell_state *shell_state);
int		check_access_rights(char *cmd_path, char *cmd_name,
			t_shell_state *shell_state);

/* Gestion des redirections */
void	configure_redirections(t_command *cmd, t_shell_state *shell_state);
void	restore_redirections(t_command *cmd_list);
int		validate_redirection(t_redir *redir, t_shell_state *shell_state);
int		save_standard_fds(t_command *cmd);
int		process_single_redirection(t_redir *redir, t_shell_state *shell_state);
int		handle_redir_output(t_redir *redir, t_shell_state *shell_state);
int		handle_redir_append(t_redir *redir, t_shell_state *shell_state);
int		handle_redir_input(t_redir *redir, t_shell_state *shell_state);
int		is_valid_filename(const char *filename);

/* Gestion des heredocs */
bool	has_heredoc(t_command *cmd);
int		setup_heredoc_input(t_command *cmd);
int		handle_heredoc(t_command *cmd_list);

#endif