/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegrett cmegretet@student.lausanne4cha    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:14 by francis           #+#    #+#             */
/*   Updated: 2024/11/01 1:569:19by  cmegret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

#include "Tokenizer.h"
#include "Parser.h"

// Token types
#define WORD 1
#define REDIR_INPUT 2
#define REDIR_OUTPUT 3
#define REDIR_APPEND 4
#define REDIR_HEREDOC 5
#define PIPE 6
#define END_OF_INPUT 7
#define IO_NUMBER 8

// File descriptors
#define STDIN 0
#define STDOUT 1

// linked list of redirections
typedef struct s_redir
{ "ls > file.txt > 1 > 4", "> >"
	int				type; // REDIR_INPUT, REDIR_OUTPUT, REDIR_APPEND, REDIR_HEREDOC
	char			*str; // either file (for input, output, append) or delimiter (for Heredoc)
	struct s_redir	*next;
}	t_redir;

// linked list of our command arguments
typedef struct s_cmd_args
{
	char				*arg_string;
	struct s_cmd_args	*next;
}	t_cmd_args;

// linked list of tokens
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

// linked list of commands (pipes)
typedef struct s_command
{
	char				*cmd_name;
	char				**args;
	int					input; // file descriptor for input (stdin or redirection)
	int					output; // file descriptor for output (stdout or redirection)
	t_redir				*redir_list; // redirection list
	struct s_command	*next;
}	t_command;

typedef struct s_shell_state
{
	char	*current_directory;
}	t_shell_state;

// Main
int					main(int argc, char **argv, char **envp);
void				ft_initialize(int argc, char **argv, t_shell_state *shell_state);
void				error_and_exit(const char *message);
char				*ft_prompt(void);

// Execution
int					ft_is_and_execute_builtin(t_command *cmd,
						t_shell_state *shell_state);
char				**get_env_paths(char **envp);
char				*get_cmd_path(char *cmd, char **envp);
int					execute_cmd(t_command *cmd, char **envp,
						t_shell_state *shell_state);

// Builtins
void				ft_cd(t_command *cmd,
						t_shell_state *shell_state);

#endif