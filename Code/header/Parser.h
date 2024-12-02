/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:40 by fallan            #+#    #+#             */
/*   Updated: 2024/12/01 18:56:23 by francis          ###   ########.fr       */
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


// OLD
int	ft_process_args(t_token *tkn, t_command *cmd_sequence);
int	ft_allocate_multiple_args(t_token *tkn,
	t_command *cmd_sequence, int arg_count);
int	ft_allocate_single_arg(t_token *tkn,
	t_command *cmd_sequence);
int	ft_count_token_list_args(t_token *tok);
// OLD

// Orchestration
t_command	*ft_parse(t_token *tok, t_shell_state *shell_state);
t_token		*ft_parse_operators(t_token *head);

// Redirections
t_redir		*ft_new_redir_node(t_redir *redir_list);
int			ft_add_redir(t_token **tok, t_command *cmd_sequence, t_redir *head_redir);

// Command arguments
int			ft_add_cmd_arg_to_list(char *tok_str, t_command *cmd_seq); // , t_cmd_args *head);
int			ft_new_cmd_arg_node(t_cmd_args *arg_list, char *arg_string);
int			ft_allocate_cmd_args_to_array(t_command *cmd_sequence);

// Utils
	// Checkers
bool		ft_token_is_redir(int token_type);
bool		ft_token_is_word(int token_type);
bool		ft_token_is_pipe(int token_type);
t_redir		*ft_last_redir(t_redir *redir_list);

	// Command arguments
int			ft_count_args(t_cmd_args *arg_list);
void		ft_free_arg_list(t_cmd_args *arg_list);

// Debug
void		ft_print_args(t_command *cmd_sequence);
int			ft_print_redirs(t_redir *redir_list);
char		*ft_return_redir_type(int redir_type);
void		ft_print_command_sequences(t_command *head);
void		ft_exit_bug_print_debugger(t_command *head);

#endif