/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/12 18:42:11 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

cat << EOF | cat << EOF2

// linked list of redirections
typedef struct s_redir
{
	int				type; // REDIR_INPUT, REDIR_OUTPUT, REDIR_APPEND, REDIR_HEREDOC
	char			*str; // either file (for input, output, append) or delimiter (for Heredoc)
	int				str_type; // the type of redirection after
	struct s_redir	*next;
}	t_redir;

void	ft_add_heredoc(t_command *cmd_list)
{
	// reprendre ft_add_redir
	
}

t_heredoc	*ft_fill_heredocs(t_command *cmd_list)
{
	t_redir	*iterator;
	
	while (cmd_list)
	{
		iterator = cmd_list->redir_list;
		while (iterator)
		{
			if (iterator->str_type == REDIR_HEREDOC) // {'<<', 'file.txt'}, {'<<', 'EOF1'}, {'<<', 'EOF2'}
				ft_add_heredoc(cmd_list);
			iterator = iterator->next;
		}
		cmd_list = cmd_list->next;
	}
	return (cmd_list-)
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

void	ft_handle_redir_heredoc(t_command *cmd_list)
{
	t_heredoc	*heredoc_list;

	while (cmd_list)
	{
		heredoc_list = cmd_list->heredoc_list;
		while (heredoc_list)
		{
			ft_prompt(REDIR_HEREDOC);
			
		}
		cmd_list = cmd_list->next;
	}
}
