/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:30:52 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/01 17:39:51 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char					*prompt;
	struct s_shell_state	shell_state;

	ft_initialize(argc, argv, &shell_state);
	prompt = ft_prompt();
	while (prompt != NULL)
	{
		add_history(prompt);
		// ft_print_token_types(ft_parse_operators(ft_tokenize(prompt)));
		execute_cmd(ft_parse(ft_tokenize(prompt)), envp, &shell_state);
		free(prompt);
		prompt = ft_prompt();
	}
	return (0);
}
