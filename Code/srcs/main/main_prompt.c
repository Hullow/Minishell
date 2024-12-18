/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/18 12:44:54 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Colors a given message with the specified ANSI color code
 *
 * Wraps a message with ANSI color codes to display colored text in terminal.
 * The color is automatically reset at the end of the message.
 *
 * @param message The message string to be colored
 * @param color The ANSI color code (e.g., "\033[32m" for green)
 * @return A newly allocated string containing the colored message
 * @note The returned string must be freed by the caller
 */
char	*ft_colorize_message(char *message, char *color)
{
	char	*colored_message;
	char	*temp;

	temp = ft_strjoin(color, message);
	colored_message = ft_strjoin(temp, "\033[0m");
	free(temp);
	return (colored_message);
}

/**
 * @brief Creates a colored prefix with an arrow and folder name
 *
 * Generates the first part of the prompt showing the current directory
 * with an arrow symbol. The arrow is green and the folder name is cyan.
 *
 * @param last_folder The name of the current directory
 * @return A newly allocated string with the formatted prefix
 * @note The returned string must be freed by the caller
 */
char	*create_prefix(char *last_folder)
{
	char	*temp1;
	char	*temp2;
	char	*result;

	temp1 = ft_colorize_message("➜  ", "\033[32m");
	temp2 = ft_colorize_message(last_folder, "\033[1;36m");
	result = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	return (result);
}

/**
 * @brief Creates a colored shell name with parentheses
 *
 * Generates the middle part of the prompt containing the shell name
 * in parentheses. The parentheses are blue and the name is red.
 *
 * @return A newly allocated string with the formatted shell name
 * @note The returned string must be freed by the caller
 */
char	*create_shell_name(void)
{
	char	*temp1;
	char	*temp2;
	char	*result;
	char	*final;

	temp1 = ft_colorize_message(" (", "\033[1;34m");
	temp2 = ft_colorize_message("Minishell", "\033[1;31m");
	result = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	temp1 = ft_colorize_message(")", "\033[1;34m");
	final = ft_strjoin(result, temp1);
	free(result);
	free(temp1);
	return (final);
}

/**
 * @brief Creates the complete shell prompt message
 *
 * Assembles all parts of the prompt:
 * 1. Arrow and current directory (green/cyan)
 * 2. Shell name in parentheses (blue/red)
 * 3. Ending colon (blue)
 *
 * @param last_folder The name of the current directory
 * @return A newly allocated string with the complete prompt
 * @note The returned string must be freed by the caller
 */
char	*ft_create_message_prompt(char *last_folder)
{
	char	*prefix;
	char	*shell;
	char	*suffix;
	char	*temp;
	char	*result;

	prefix = create_prefix(last_folder);
	shell = create_shell_name();
	suffix = ft_colorize_message(" : ", "\033[1;34m");
	temp = ft_strjoin(prefix, shell);
	result = ft_strjoin(temp, suffix);
	free(prefix);
	free(shell);
	free(suffix);
	free(temp);
	return (result);
}

/**
 * @brief Generates the appropriate prompt based on context
 *
 * Creates either:
 * 1. A simple heredoc prompt ("> ")
 * 2. A full custom prompt with current directory and shell info
 *
 * Error handling:
 * - Returns simple "Minishell : " prompt if getcwd fails
 * - Exits with failure status on memory allocation errors
 * - Handles invalid path formats gracefully
 *
 * @param type REDIR_HEREDOC for heredoc prompt, 0 for normal prompt
 * @return A newly allocated string containing user input
 * @note The returned string must be freed by the caller
 */
char	*ft_prompt(int type)
{
	char	*prompt;
	char	cwd[1024];
	char	*last_folder;
	char	*message;

	if (type == REDIR_HEREDOC)
		return (readline("> "));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (readline("Minishell : "));
	}
	last_folder = ft_strrchr(cwd, '/');
	if (last_folder == NULL)
		return (readline("Minishell : "));
	last_folder++;
	message = ft_create_message_prompt(last_folder);
	if (message == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	prompt = readline(message);
	free(message);
	return (prompt);
}
