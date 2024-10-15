/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:30:52 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/15 14:44:34 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char					*prompt;
	struct s_shell_state	shell_state;

	ft_initialize(argc, argv, &shell_state, envp);
	prompt = ft_prompt();
	while (prompt != NULL)
	{
		if (prompt[0] == '\0')  // Si prompt est vide, cela signifie que ctrl-D a été pressé
		{
			free(prompt);
			break;  // Sortir de la boucle pour terminer le shell
		}
		add_history(prompt);
		//ft_tokenization_checker(ft_parse_operators(ft_tokenize(prompt)));
		execute_cmd(ft_parse(ft_tokenize(prompt)), envp, &shell_state);
		free(prompt);
		prompt = ft_prompt();
	}
	return (0);
}
