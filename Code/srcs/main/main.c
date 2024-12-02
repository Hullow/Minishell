/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:30:52 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/02 18:28:39 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*prompt;
	t_shell_state	shell_state;
	t_command		*cmd_sequence;
	t_token			*token_list;

	ft_initialize(argc, argv, &shell_state, envp);
	prompt = ft_prompt();
	while (prompt != NULL)
	{
		add_history(prompt);
		//ft_tokenization_checker(ft_parse_operators(ft_tokenize(prompt)));
		token_list = ft_tokenize(prompt);
		cmd_sequence = ft_parse(token_list, &shell_state);
		ft_exit_bug_print_debugger(cmd_sequence); // prevents the "exit bug"
		// ft_print_command_sequences(cmd_sequence);
		execute_cmd(cmd_sequence, shell_state. envp, &shell_state);
		free(prompt);
		prompt = ft_prompt();
	}
	return (0);
}
