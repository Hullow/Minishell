/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:48:46 by fallan            #+#    #+#             */
/*   Updated: 2024/12/20 16:18:24 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "Minishell.h"

typedef struct s_redir			t_redir;
typedef struct s_token			t_token;
typedef struct s_cmd_args		t_cmd_args;
typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;

// Tokenization functions
	// General
t_token		*ft_tokenize(char *prompt);
int			ft_process_prompt(char *prompt, int i, t_token **tok);
t_token		*ft_create_token(int token_type);
t_token		*ft_add_token_to_list(t_token *tok, int token_type);
void		ft_set_empty_token_strings(t_token *tok);

	// Words and strings
int			ft_new_word(t_token **tok, char c);
int			ft_append_char_to_word(t_token **tok, char c);
void		ft_set_empty_token_strings(t_token *tok);
t_token		*ft_tokenize_end_of_input(t_token *tok);
int			ft_tokenize_blank(t_token **tok);
	// Operators
int			ft_continue_operator_token(char *prompt, int i, t_token **tok);
int			ft_new_operator_token(char *prompt, int i, t_token **tok);
void		ft_set_operator_token(char c, t_token **tok);
	// Quotes
int			ft_handle_quote_tokenization(char c,
				bool single_quoted, bool double_quoted, t_token **tok);
	// Expansions
int			ft_check_parameter_start(char c1, char c2);
void		ft_prepare_expansion(t_token **tok);

// Checkers
	// Simple characters
int			ft_is_operator_character(char c);
int			ft_is_blank(char c);
int			ft_is_quote_character(char c);
bool		ft_is_dollar_sign(char c);
	// Tokens
int			ft_token_has_open_quote(t_token *tok);
int			ft_check_open_quote(t_token *tok);
int			ft_previous_char_is_undelimited_operator(t_token *tok);
int			ft_previous_char_part_of_word(t_token *tok);

// Debugging
t_token		*ft_last_token(t_token *tok);
int			ft_count_tokens(t_token *tok);
void		ft_print_token_types_and_quote_status(t_token *tok);
void		ft_print_required_expansions(t_token *tok);

// Utils
void		ft_free_token_list(t_token *token_list);

#endif