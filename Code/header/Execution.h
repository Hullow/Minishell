/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:38 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/01 18:46:10 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "Minishell.h"

typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Execution
int		ft_is_and_execute_builtin(t_command *cmd, t_shell_state *shell_state);
char	**get_env_paths(char **envp);
char	*get_cmd_path(char *cmd, char **envp);
int	execute_cmd(t_command *cmd, char **envp, t_shell_state *shell_state);

#endif