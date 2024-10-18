/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:14 by francis           #+#    #+#             */
/*   Updated: 2024/10/18 20:04:31 by fallan           ###   ########.fr       */
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
};

// Main
int					main(int argc, char **argv, char **envp);
void				ft_initialize(int argc, char **argv, struct s_shell_state *shell_state);
void				error_and_exit(const char *message);
char				*ft_prompt(void);

// Execution
int					ft_is_and_execute_builtin(struct s_command *cmd,
						struct s_shell_state *shell_state);
char				**get_env_paths(char **envp);
char				*get_cmd_path(char *cmd, char **envp);
int					execute_cmd(struct s_command *cmd, char **envp,
						struct s_shell_state *shell_state);

// Builtins
void				ft_cd(struct s_command *cmd,
						struct s_shell_state *shell_state);