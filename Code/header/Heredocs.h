/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:40:32 by fallan            #+#    #+#             */
/*   Updated: 2024/12/24 13:45:36 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOCS_H
# define HEREDOCS_H

# include "Minishell.h"

typedef struct s_heredoc	t_heredoc;
typedef struct s_token		t_token;

/*
** Main Heredoc Functions (heredocs_main.c)
*/
void		ft_open_heredocs(t_command *cmd_list, t_shell_state *shell_state);
void		ft_handle_heredoc_input(t_redir *redir_list,
				t_shell_state *shell_state);
int			process_heredoc(t_heredoc **heredoc_line, t_redir *redir_list,
				t_shell_state *shell_state);

/*
** Heredoc Utils (heredocs_utils.c)
*/
bool		ft_match_heredoc_delimiter(char *heredoc_line, char *delimiter);
t_heredoc	*ft_init_heredoc(void);
t_heredoc	*initialize_heredoc(t_redir *redir_list);

/*
** Heredoc Read Functions (heredocs_read.c)
*/
bool		read_and_process_line(t_heredoc **heredoc_line,
				t_redir *redir_list, t_shell_state *shell_state);
t_heredoc	*ft_malloc_new_heredoc_line(t_heredoc *heredoc_line);

#endif