/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:48:46 by fallan            #+#    #+#             */
/*   Updated: 2024/10/18 20:03:10 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Tokenization
struct s_token		*ft_create_new_token(struct s_token *tok);
struct s_token		*ft_tokenize_end_of_input(struct s_token *tok);
int					ft_continue_operator_token(char *prompt, int i,
						struct s_token **tok);
int					ft_new_operator_token(char *prompt, int i,
						struct s_token **tok);
int					ft_tokenize_blank(struct s_token **tok);
int					ft_append_char_to_word(struct s_token **tok, char c);
int					ft_new_word(struct s_token **tok, char c);
struct s_token		*ft_tokenize(char *prompt);

// Checkers
int					ft_previous_char_is_undelimited_operator(struct s_token *tok);
int					ft_is_operator_character(char c);
int					ft_is_blank(char c);
int					ft_previous_char_part_of_word(struct s_token *tok);

// Tokenization utils
void				ft_tokenization_checker(struct s_token *head);
int					ft_count_tokens(struct s_token *tok);
