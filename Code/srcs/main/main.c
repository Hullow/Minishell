/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:54:34 by francis           #+#    #+#             */
/*   Updated: 2024/12/20 13:07:28 by cmegret          ###   ########.fr       */
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
	prompt = ft_prompt(0);
	while (prompt != NULL)
	{
		if (*prompt)
			add_history(prompt);
		token_list = ft_tokenize(prompt);
		cmd_list = ft_parse(token_list);
		ft_open_heredocs(cmd_list, &shell_state);
		if (g_signal)
		{
			g_signal = 0;
			ft_free_all(prompt, token_list, cmd_list);
			prompt = ft_prompt(0);
			continue ;
		}
		expand_command_variables(cmd_list, &shell_state);
		execute_cmd(cmd_list, &shell_state);
		ft_free_all(prompt, token_list, cmd_list);
		prompt = ft_prompt(0);
	}
	rl_clear_history();
	ft_free_shell_state(&shell_state);
	return (0);
}
