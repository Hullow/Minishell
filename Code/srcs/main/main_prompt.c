/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/18 12:23:51 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

/**
 * @brief Colors a given message with the specified ANSI color code.
 *
 * This function takes a message and a color code as input,
 * and returns the message wrapped with the ANSI color code.
 *
 * @param message The message to be colored.
 * @param color The ANSI color code to apply to the message.
 * @return A new string with the colored message.
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
 * @brief Creates a colored prompt message for the shell.
 *
 * This function constructs a prompt message by combining
 * various parts of the prompt, each colored differently using ANSI color codes.
 * The prompt includes an arrow, the current directory, and the shell name
 * "Minishell".
 *
 * @param last_folder The name of the last folder in the current
 * working directory.
 * @return A new string with the complete colored prompt message.
 */
char	*ft_create_message_prompt(char *last_folder)
{
	char	*message;

	message = ft_strjoin(ft_colorize_message("➜  ", "\033[32m"),
			ft_colorize_message(last_folder, "\033[1;36m"));
	message = ft_strjoin(message, ft_colorize_message(" (", "\033[1;34m"));
	message = ft_strjoin(message,
			ft_colorize_message("Minishell", "\033[1;31m"));
	message = ft_strjoin(message, ft_colorize_message(")", "\033[1;34m"));
	message = ft_strjoin(message, ft_colorize_message(" : ", "\033[1;34m"));
	return (message);
}

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
