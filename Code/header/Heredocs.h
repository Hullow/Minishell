/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:40:32 by fallan            #+#    #+#             */
/*   Updated: 2024/12/13 20:21:07 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOCS_H
# define HEREDOCS_H

#include "Minishell.h"

typedef struct s_heredoc	t_heredoc;
typedef struct s_token		t_token;

void		ft_open_heredocs(t_command *cmd_list);
void		ft_handle_heredoc_input(t_redir *redir_list);
t_heredoc	*ft_init_heredoc(void);
t_heredoc	*ft_malloc_new_heredoc_line(t_heredoc *heredoc_line);
bool		ft_match_heredoc_delimiter(char *heredoc_line, char *delimiter);

// Debugging
void		ft_print_heredocs(t_command *cmd_list);


#endif