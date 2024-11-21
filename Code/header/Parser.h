/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:40 by fallan            #+#    #+#             */
/*   Updated: 2024/11/21 16:23:26 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "Minishell.h"

typedef struct s_redir			t_redir;
typedef struct s_token			t_token;
typedef struct s_cmd_args		t_cmd_args;
typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Orchestration
t_command	*ft_parse(t_token *tok, t_shell_state *shell_state);
t_token		*ft_parse_operators(t_token *head);

// Redirections
t_redir		*ft_new_redir_node(t_redir *redir_list);
int			ft_add_redir(t_token **tok, t_command *cmd_sequence);

// Command arguments
int			ft_add_cmd_arg(char *tok_str, t_command *cmd_seq);
int			ft_new_cmd_arg_node(t_cmd_args *arg_list, char *arg_string);
int			ft_allocate_args(t_command *cmd_sequence, t_cmd_args *arg_list);

// Utils
	// Checkers
bool		ft_token_is_redir(int token_type);
bool		ft_token_is_word(int token_type);
t_redir		*ft_last_redir(t_redir *redir_list);

	// Command arguments
void		ft_print_args(t_command *cmd_sequence);
int			ft_count_args(t_cmd_args *arg_list);
void		ft_free_arg_list(t_cmd_args *arg_list);

	// Other
int			ft_print_redirs(t_redir *redir_list);
char		*ft_return_redir_type(int redir_type);

#endif