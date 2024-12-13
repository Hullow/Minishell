/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:40:32 by fallan            #+#    #+#             */
/*   Updated: 2024/12/13 00:24:34 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOCS_H
# define HEREDOCS_H

#include "Minishell.h"

typedef struct s_heredoc	t_heredoc;

void		ft_open_heredocs(t_command *cmd_list);
void		ft_handle_heredoc_input(t_redir *redir_list);
t_heredoc	*ft_init_heredoc(void);
int			ft_malloc_heredoc_line(t_heredoc **heredoc_line);
bool		ft_match_heredoc_delimiter(char **line, char *delimiter);

	// Line split
char		**ft_split_heredoc_line(char const *str);
int			ft_apply_heredoc_line_split(char const *s, char **ret);
int			ft_add_heredoc_line_splitted(char const *s, \
				int start, int end, char **ret);
int			ft_calc_heredoc_line_size(char const *s);

#endif