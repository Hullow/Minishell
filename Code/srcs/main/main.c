/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:30:52 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/14 17:20:12 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char					*prompt;
	struct s_shell_state	shell_state;

	ft_initialize(argc, argv, &shell_state);
	prompt = readline("Minishell : ");
	while (prompt != NULL)
	{
		add_history(prompt);
		ft_tokenization_checker(ft_parse_operators(ft_tokenize(prompt)));
		execute_cmd(ft_parse(ft_tokenize(prompt)), envp, &shell_state);
		free(prompt);
		prompt = readline("Minishell : ");
	}
	return (0);
}
