/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:48:46 by fallan            #+#    #+#             */
/*   Updated: 2024/11/01 18:54:10 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "Minishell.h"

typedef struct s_redir			t_redir;
typedef struct s_token			t_token;
typedef struct s_cmd_args		t_cmd_args;
typedef struct s_command		t_command;
typedef struct s_shell_state	t_shell_state;


// Tokenization
t_token		*ft_create_new_token(t_token *tok);
t_token		*ft_tokenize_end_of_input(t_token *tok);
int					ft_continue_operator_token(char *prompt, int i,
						t_token **tok);
int					ft_new_operator_token(char *prompt, int i,
						t_token **tok);
int					ft_tokenize_blank(t_token **tok);
int					ft_append_char_to_word(t_token **tok, char c);
int					ft_new_word(t_token **tok, char c);
t_token		*ft_tokenize(char *prompt);

// Checkers
int					ft_previous_char_is_undelimited_operator(t_token *tok);
int					ft_is_operator_character(char c);
int					ft_is_blank(char c);
int					ft_previous_char_part_of_word(t_token *tok);

// Tokenization utils
t_token 		*ft_last_token(t_token *tok);
int					ft_count_tokens(t_token *tok);
void				ft_print_all_token_strings(t_token **head);
void				ft_print_token_types(t_token *head);
void				ft_free_token(t_token *tok);

#endif