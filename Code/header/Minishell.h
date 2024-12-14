/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:55:06 by yourlogin         #+#    #+#             */
/*   Updated: 2024/12/07 13:55:06 by yourlogin        ###   ########.ch       */
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
# include <fcntl.h>

# ifndef ECHOCTL
#  define ECHOCTL 0x00000040
# endif

# ifndef NAME_MAX
#  define NAME_MAX 255
# endif

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include "Builtin.h"
# include "Execution.h"
# include "Signal.h"
# include "Expansion.h"
# include "Tokenizer.h"
# include "Parser.h"

// Token types
# define WORD 1
# define REDIR_INPUT 2
# define REDIR_OUTPUT 3
# define REDIR_APPEND 4
# define REDIR_HEREDOC 5
# define PIPE 6
# define END_OF_INPUT 7
# define IO_NUMBER 8

// File descriptors
# define STDIN 0
# define STDOUT 1

extern int	g_signal;

// linked list of redirections
typedef struct s_redir
{
	int				type; // REDIR_INPUT, REDIR_OUTPUT, REDIR_APPEND, REDIR_HEREDOC
	char			*str; // either file (for input, output, append) or delimiter (for Heredoc)
	int				str_type; // the type of redirection after
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
	bool			is_double_quoted;
	bool			is_single_quoted;
	bool			is_operator;
	struct s_token	*next;
}	t_token;

// linked list of commands (pipes)
// n.b.: **args is the array of arguments used by execve,
//		 while *arg_list is the list of arguments filled by our parser
typedef struct s_command
{
	char				*cmd_name;
	t_cmd_args			*arg_list;
	char				**args;
	int					saved_input; // file descriptor for input (stdin or redirection)
	int					saved_output; // file descriptor for output (stdout or redirection)
	t_redir				*redir_list; // redirection list
	struct s_command	*next;
}	t_command;

typedef struct s_shell_state
{
	char	**envp;
	int		last_exit_status;
}	t_shell_state;

typedef struct s_params
{
	char	*arg;
	int		*j;
	char	**table;
	int		*word_count;
}	t_params;

// Main
int			main(int argc, char **argv, char **envp);
void		ft_initialize(int argc, char **argv,
				t_shell_state *shell_state, char **envp);
void		error_and_exit(const char *message, int last_exit_status);
void		check_arguments(int argc, char **argv);

// Prompt
char		*ft_prompt(void);

// Utils
void		ft_free_cmd_list(t_command *head_cmd);

#endif