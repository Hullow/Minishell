/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2025/01/02 19:39:58 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Prints a formatted error message to standard error.
 *
 * This function displays a bash-style error message on STDERR (fd 2).
 * Format: "minishell: [cmd]: [arg]: message\n"
 * Both cmd and arg parameters are optional and can be NULL.
 *
 * @param cmd The command that generated the error (can be NULL)
 * @param arg The argument that caused the error (can be NULL)
 * @param message The main error message to display
 */
void	ft_print_error(char *cmd, char *arg, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
}

/**
 * @brief Generates the appropriate prompt based on context
 *
 * @param last_folder Current working directory's last folder name
 *
 * @details
 * Builds a prompt string in the format:
 * "➜  {last_folder} (Minishell) : "
 *
 * @note Memory management:
 * - Returns newly allocated string
 * - Caller must free the returned string
 * - Handles intermediate memory allocations internally
 *
 * @return Formatted prompt string, or NULL if allocation fails
 */
char	*ft_create_message_prompt(char *last_folder)
{
	char	*message;
	char	*tmp;

	message = ft_strjoin("➜  ", last_folder);
	tmp = ft_strjoin(message, " (");
	free(message);
	message = ft_strjoin(tmp, "Minishell");
	free(tmp);
	tmp = ft_strjoin(message, ") : ");
	free(message);
	return (tmp);
}

/**
 * Generates the shell prompt based on context
 *
 * @param type REDIR_HEREDOC for heredoc prompt, 0 for normal prompt
 *
 * @details
 * Creates one of two prompts:
 * 1. Simple heredoc prompt ("> ")
 * 2. Full prompt with current directory: "➜  {folder} (Minishell) : "
 *
 * Error handling:
 * - Returns "minishell: " if getcwd fails
 * - Handles null/invalid paths gracefully
 *
 * @note Memory management:
 * - Returns newly allocated string from readline
 * - Caller must free the returned string
 *
 * @return User input string, or NULL on EOF
 */
char	*ft_prompt(int type)
{
	// char	*prompt;
	// char	*message;
	// char	cwd[1024];
	// char	*last_folder;

	if (type == REDIR_HEREDOC)
		return (readline("> "));
	// if (getcwd(cwd, sizeof(cwd)) != NULL)
	// {
	// 	last_folder = ft_strrchr(cwd, '/');
	// 	if (last_folder != NULL)
	// 		last_folder++;
	// 	message = ft_create_message_prompt(last_folder);
	// 	prompt = readline(message);
	// 	free(message);
	// 	return (prompt);
	// }
	return (readline("minishell: "));
}
