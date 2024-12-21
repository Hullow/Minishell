/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:44:40 by fallan            #+#    #+#             */
/*   Updated: 2024/12/21 16:53:02 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "Minishell.h"

typedef struct s_redir			t_redir;
typedef struct s_token			t_token;
typedef struct s_cmd_args		t_cmd_args;
typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Orchestration
t_command	*ft_parse(t_token *tok);
t_token		*ft_parse_operators(t_token *head);

// Redirections
int			ft_add_redir(t_token **tok, t_command *cmd_list);
t_redir		*ft_create_redir(t_command *cmd_list);
t_token		**ft_assign_redir_str(t_token **tok, t_redir *redir_list);
t_redir		*ft_last_redir(t_redir *redir_list);

// Command arguments allocation
int			ft_add_cmd_arg_to_list(t_token *tok, t_cmd_args **arg_list,
				t_cmd_args *head);
int			ft_new_cmd_arg_node(t_cmd_args *arg_list, char *arg_string);
int			ft_allocate_cmd_args_to_array(t_command *cmd_list);
int			ft_copy_command_args(t_command *cmd, int arg_count);
int			ft_count_args(t_cmd_args *arg_list);

// Utils
	// Checkers
bool		ft_token_is_redir(int token_type);
bool		ft_token_is_word(int token_type);
bool		ft_token_is_pipe(int token_type);

// Debug
void		ft_print_args(t_command *cmd_list);
void		ft_print_redirs(t_redir *redir, char *cmd_name);
void		ft_print_all_redirs(t_command *cmd);
char		*ft_return_redir_type(int redir_type);
void		ft_print_command_sequences(t_command *head);

#endif