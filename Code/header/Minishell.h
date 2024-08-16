/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:14 by francis           #+#    #+#             */
/*   Updated: 2024/08/16 12:04:58 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h> 

#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"

// Token types
#define WORD 1
#define NEWLINE 2
#define REDIR_INPUT 3
#define REDIR_OUTPUT 4
#define REDIR_APPEND 5
#define REDIR_HEREDOC 6
#define PIPE 7
#define END_OF_INPUT 8

#include <stdbool.h>
struct token
{
	char 			*str;
	int 			type;
	bool			is_delimited;
	bool			is_quoted;
	// bool			is_double_quoted;
	// bool			is_single_quoted;
	bool			is_operator;
	struct token	*next;
};

struct command
{
	char *cmd_name;
	char **args;
	int fd; // redirection
	struct command *next;
};

// Tokenisation
	// Checkers
int	ft_previous_char_is_undelimited_operator(struct token *tok);
int	ft_is_operator_character(char c);
int	ft_is_blank(char c);
int	ft_previous_char_part_of_word(struct token *tok);
	// tokenizers
struct token	*ft_tokenize(char *prompt);

// Parsing
struct command	*ft_parse(struct token *head);
struct token	*ft_parse_operators(struct token *head);

	// Parsing utils
int	ft_count_token_list_args(struct token *tok);

// Execution
int		execute_cmd(struct command *cmd, char **envp);

// debugging
	// Parsing
void	ft_tokenization_checker(struct token *head);