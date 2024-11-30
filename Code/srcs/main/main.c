/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:30:52 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/30 19:56:37 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

t_command *ft_debug_parsing(t_token *tok)
{
	t_command	*cmd_sequence;
	int			i;

	cmd_sequence = malloc (sizeof(t_command));
	if (!cmd_sequence)
		return (NULL);
	if (tok && tok->type == END_OF_INPUT)
		printf("end of input token tokenized\n");
	cmd_sequence->args = malloc (2 * sizeof(char *));
	if (tok && tok->str)
	{
		cmd_sequence->cmd_name = ft_strdup(tok->str);
		cmd_sequence->args[0] = ft_strdup(tok->str);
		tok = tok->next;
	}
	if (cmd_sequence->cmd_name == NULL || ft_strlen(cmd_sequence->cmd_name) == 0) // or ft_strlen ((*cmd_sequence)->cmd_name == NULL))
		return (NULL);
	i = 1;
	while (tok)
	{	
		cmd_sequence->args = realloc (cmd_sequence->args, (i + 2) * sizeof(char *));
		if (tok->str)
			cmd_sequence->args[i] = ft_strdup(tok->str);
		else
		{
			printf("ft_debug – tok: {%p}, no tok->str\n", tok);
			cmd_sequence->args[i] = NULL;
			return (cmd_sequence);
		}
		i++;
		tok = tok->next;
	}
	cmd_sequence->args[i] = NULL;
	return (cmd_sequence);
}

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
