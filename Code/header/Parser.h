/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:40 by fallan            #+#    #+#             */
/*   Updated: 2024/10/31 17:58:04 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "Minishell.h"

typedef struct s_redir s_redir;

// Orchestration
struct s_command	*ft_parse(struct s_token *head);
struct s_token		*ft_parse_operators(struct s_token *head);

// Redirections
s_redir				*ft_parse_redirections(struct s_token **tok);
s_redir				*ft_create_redir_node(struct s_token *tok, s_redir *redir_list);
s_redir				*ft_create_redir_list(struct s_token *tok);
s_redir				*ft_last_redir(s_redir *redir_list);
bool				ft_is_redir(int token_type);

#endif