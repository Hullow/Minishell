/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:14 by francis           #+#    #+#             */
/*   Updated: 2024/11/21 16:33:17 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include "Builtin.h"
# include "Execution.h"
# include "Signal.h"
# include "Pathname.h"

// Token types
# define WORD 1
# define MINISHELL_NEWLINE 2
# define REDIR_INPUT 3
# define REDIR_OUTPUT 4
# define REDIR_APPEND 5
# define REDIR_HEREDOC 6
# define PIPE 7
# define END_OF_INPUT 8
# define SUFFIX 9 // TEMPORARY, FOR TESTING PURPOSES, REMOVE AFTERWARDS

extern int	g_signal;

typedef struct s_token
{
	char			*str;
	int				type;
	bool			is_delimited;
	bool			is_quoted;
	// bool			is_double_quoted;
	// bool			is_single_quoted;
	bool			is_operator;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*cmd_name;
	char				**args;
	int					fd; // redirection
	struct s_command	*next;
}	t_command;

typedef struct s_shell_state
{
	char	**envp;
	int		last_exit_status;
}	t_shell_state;

// Main
int			main(int argc, char **argv, char **envp);
void		ft_initialize(int argc, char **argv,
				t_shell_state *shell_state, char **envp);
void		error_and_exit(const char *message, int last_exit_status);
char		*ft_prompt(void);

// Tokenization
t_token		*ft_create_new_token(t_token *tok);
t_token		*ft_tokenize_end_of_input(t_token *tok);
int			ft_continue_operator_token(char *prompt, int i,
				t_token **tok);
int			ft_new_operator_token(char *prompt, int i,
				t_token **tok);
int			ft_tokenize_blank(t_token **tok);
int			ft_append_char_to_word(t_token **tok, char c);
int			ft_new_word(t_token **tok, char c);
t_token		*ft_tokenize(char *prompt);
int			ft_previous_char_is_undelimited_operator(t_token *tok);
int			ft_is_operator_character(char c);
int			ft_is_blank(char c);
int			ft_previous_char_part_of_word(t_token *tok);
t_token		*ft_init_token(void);

// Parsing
t_token		*ft_parse_operators(t_token *head);
void		ft_tokenization_checker(t_token *head);
t_command	*ft_parse(t_token *head);
int			ft_count_token_list_args(t_token *tok);

#endif