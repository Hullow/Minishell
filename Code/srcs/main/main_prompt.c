/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:40:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/18 16:34:18 by cmegret          ###   ########.fr       */
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
	if (type == REDIR_HEREDOC)
		return (readline("> "));
	else
		return (readline("Minishell : "));
}
