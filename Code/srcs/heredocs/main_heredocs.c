/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/12 19:01:40 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// prompt, parse et enregistre donnees d'input dans une liste chainee de heredoc
void	ft_open_and_store_heredoc(t_command *cmd_list)
{
	char	*prompt;

	prompt = ft_prompt(REDIR_HEREDOC);
	while (prompt != NULL)
	{
		ft_prompt(REDIR_HEREDOC);
		ft_tokenize_parse_expand_heredoc(); //ft_isspace, ft_check_expansion, ft_expand
		
		prompt = ft_prompt(REDIR_HEREDOC);
	}
	ft_tokenize_heredoc
	open()
}


/**
 * @brief Handles input redirection.
 * 
 * This function opens the file specified in the redirection structure
 * for reading. It then duplicates the file descriptor to STDIN_FILENO.
 * 
 * @param redir The redirection structure containing the file information.
 * @param shell_state The current state of the shell.
 * @return 0 on success, -1 on failure.
 */
static int	handle_redir_input(t_redir *redir, t_shell_state *shell_state)
{
	int	fd;

	fd = open(redir->str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		shell_state->last_exit_status = 1;
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}


// parcourir les commandes et les listes de redirections
// si on tombe sur un heredoc, on l'ouvre, et on stocke 
t_heredoc	*ft_fill_heredocs(t_command *cmd_list)
{
	t_redir	*iterator;
	
	while (cmd_list)
	{
		iterator = cmd_list->redir_list;
		while (iterator)
		{
			if (iterator->str_type == REDIR_HEREDOC) // {'<<', 'file.txt'}, {'<<', 'EOF1'}, {'<<', 'EOF2'}
				ft_open_and_store_heredoc(cmd_list);
			iterator = iterator->next;
		}
		cmd_list = cmd_list->next;
	}
	return (cmd_list);
}

// 2.7 Redirection
//  Redirection is used to open and close files 
//  for the current shell execution environment (see 2.13 Shell Execution Environment) 
//  or for any command. 
//  Redirection operators can be used with numbers representing file descriptors as described below.
 
// 2.7.4 Here-Document

// The redirection operators "<<" allows redirection of subsequent lines read by the shell 
// to the input of a command. 
// The redirected lines are known as a "here-document".
// The here-document shall be treated as a single word 
// that begins after the next NEWLINE token,
//  and continues until there is a line containing only the delimiter 
//  and a <newline>, with no <blank> characters in between.

