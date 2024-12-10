/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:36:43 by francis           #+#    #+#             */
/*   Updated: 2024/12/10 18:07:08 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*prompt;
	t_shell_state	shell_state;
	t_command		*cmd_list;
	t_token			*token_list;

	ft_initialize(argc, argv, &shell_state, envp);
	prompt = ft_prompt();
	while (prompt != NULL)
	{
		if (*prompt)
			add_history(prompt);
		//ft_tokenization_checker(ft_parse_operators(ft_tokenize(prompt)));
		token_list = ft_tokenize(prompt);
		cmd_list = ft_parse(token_list, &shell_state);
		expand_command_variables(cmd_list, &shell_state);
		// ft_exit_bug_print_debugger(cmd_list); // prevents the "exit bug"
		// ft_print_command_sequences(cmd_list);
		execute_cmd(cmd_list, &shell_state);
		free(prompt);
		prompt = ft_prompt();
	}
	return (0);
}
