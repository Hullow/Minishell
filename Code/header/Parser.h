/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:40 by fallan            #+#    #+#             */
/*   Updated: 2024/11/01 17:32:36 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "Minishell.h"

typedef struct s_redir s_redir;
typedef struct s_cmd_args s_cmd_args;

// Orchestration
struct s_command	*ft_parse(struct s_token *head);
struct s_token		*ft_parse_operators(struct s_token *head);

// Redirections
s_redir				*ft_new_redir_node(s_redir *redir_list);
int					ft_add_redir(struct s_token **tok, s_redir *redir_list);

// Command arguments
int					ft_add_cmd_arg(char *tok_str, struct s_command *cmd_seq, s_cmd_args *arg_list);
int					ft_new_cmd_arg_node(s_cmd_args *arg_list, char *arg_string);
int					ft_allocate_args(struct s_command *cmd_sequence, s_cmd_args *arg_list);

// Utils
bool				ft_token_is_redir(int token_type);
bool				ft_token_is_word(int token_type);
int					ft_count_args(s_cmd_args *arg_list);
void				ft_free_arg_list(s_cmd_args *arg_list);
s_redir				*ft_last_redir(s_redir *redir_list);

#endif