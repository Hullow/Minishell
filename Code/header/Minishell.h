/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:55:06 by yourlogin         #+#    #+#             */
/*   Updated: 2024/12/24 13:59:22 by cmegret          ###   ########.fr       */
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
# include "Expansion.h"
# include "Heredocs.h"
# include "Parser.h"
# include "Signal.h"
# include "Tokenizer.h"

// Token types
# define UNKNOWN_TYPE 0
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

# define SIGNAL_HEREDOC 128
# define SIGNAL_NONE 0
# define SIGNAL_INT 128

extern int	g_signal;

// a linked list storing the contents of one heredoc
// each node of the list is a line of a heredoc
// => each list stores the entire contents of one heredoc
typedef struct s_heredoc
{
	char				*line;
	struct s_heredoc	*next;
}	t_heredoc;

// linked list of redirections
typedef struct s_redir
{
	int				type; // REDIR_: INPUT, OUTPUT, APPEND, HEREDOC (#define)
	char			*str; //file (input, output, append) or delimiter (Heredoc)
	int				str_type; // type of the token following the redirection
	t_expand		*to_expand; // expansion of redirection string
	t_heredoc		*heredoc; // heredoc contents, if redirection is a heredoc
	bool			expand_heredoc; // false if delimiter is quoted, else true
	struct s_redir	*next;
}	t_redir;

// if check == true, need to expand
// else, no need to expand
typedef struct s_expand
{
	bool			check;
	int				size_to_expand;
	struct s_expand	*next;
}	t_expand;

// linked list of our command arguments
typedef struct s_cmd_args
{
	char				*arg_string;
	t_expand			*to_expand;
	struct s_cmd_args	*next;
}	t_cmd_args;

// linked list of tokens
typedef struct s_token
{
	char			*str;
	int				type;
	bool			is_delimited;
	bool			is_operator;
	t_expand		*to_expand;
	bool			is_double_quoted;
	bool			is_single_quoted;
	bool			is_between_quotes;
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
	int					saved_input; // fd for input (stdin or redirection)
	int					saved_output; // fd for output (stdout or redirection)
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
void		check_arguments(int argc, char **argv, t_shell_state *shell_state);

// Prompt
char		*ft_prompt(int type);

// Free
void		ft_free_all(char *prompt, t_token *token_list, t_command *cmd);
void		ft_free_cmd_list(t_command *cmd);
void		ft_free_array_of_strings(char **args);
void		ft_free_arg_list(t_cmd_args	*arg_list);
void		ft_free_redir_list(t_redir *redir_list);
void		ft_free_shell_state(t_shell_state *shell_state);

#endif