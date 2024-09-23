/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:14 by francis           #+#    #+#             */
/*   Updated: 2024/09/23 14:58:56 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

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
#define SUFFIX 9 // TEMPORARY, FOR TESTING PURPOSES, REMOVE AFTERWARDS

struct s_token
{
	char			*str;
	int				type;
	bool			is_delimited;
	bool			is_quoted;
	// bool			is_double_quoted;
	// bool			is_single_quoted;
	bool			is_operator;
	struct s_token	*next;
};

struct s_command
{
	char				*cmd_name;
	char				**args;
	int					fd; // redirection
	struct s_command	*next;
};

struct s_shell_state
{
	char	*current_directory;
	char	**envp;
};

// Main
int					main(int argc, char **argv, char **envp);
void				ft_initialize(int argc, char **argv,
						struct s_shell_state *shell_state, char **envp);
void				error_and_exit(const char *message);
char				*ft_prompt(void);

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
int					ft_previous_char_is_undelimited_operator(struct s_token *tok);
int					ft_is_operator_character(char c);
int					ft_is_blank(char c);
int					ft_previous_char_part_of_word(struct s_token *tok);

// Parsing
struct s_token		*ft_parse_operators(struct s_token *head);
void				ft_tokenization_checker(struct s_token *head);
struct s_command	*ft_parse(struct s_token *head);
int					ft_count_token_list_args(struct s_token *tok);

// Execution
int					ft_is_and_execute_builtin(struct s_command *cmd,
						struct s_shell_state *shell_state);
char				**get_env_paths(char **envp);
char				*get_cmd_path(char *cmd, char **envp);
int					execute_cmd(struct s_command *cmd, char **envp,
						struct s_shell_state *shell_state);

// Builtin cd
void				ft_cd(struct s_command *cmd,
						struct s_shell_state *shell_state);

// Builtin env
void				ft_env(char **envp);

// Builtin export
void				ft_export(char ***envp, const char *var);
const char			*extract_value(const char *new_value);
char				*build_new_var(const char *name, const char *value);
int					find_var_index(char **envp, char *name, size_t name_len);
int					update_existing_var(char ***envp, char *name,
						const char *new_value);
void				add_new_var(char ***envp, const char *var);
char				*get_var_name(const char *var);

// Builtin unset
void				ft_unset(char ***envp, const char *var);