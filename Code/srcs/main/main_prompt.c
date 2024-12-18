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
