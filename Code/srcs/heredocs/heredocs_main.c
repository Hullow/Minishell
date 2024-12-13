/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/13 01:15:03 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// 2.7 Redirection
//  Redirection is used to open and close files 
//  for the current shell execution environment or for any command.

	// 2.7.4 Here-Document
// The redirection operators "<<" allows redirection 
// of subsequent lines read by the shell 
// to the input of a command.
//
// The redirected lines are known as a "here-document".
// The here-document shall be treated as a single word 
// that begins after the next NEWLINE token,
//  and continues until there is a line containing only the delimiter 
//  and a <newline>, with no <blank> characters in between.


// mallocs the first node of our heredoc
// (which is a linked list of heredoc lines)
t_heredoc	*ft_init_heredoc(void)
{
	t_heredoc	*heredoc_line;

	heredoc_line = malloc(sizeof(t_heredoc));
	if (!heredoc_line)
		return (NULL);
	heredoc_line->contents = NULL;
	heredoc_line->next = NULL;
	return (heredoc_line);
}

// mallocs a new heredoc line and sets heredoc_line to the 
int	ft_malloc_heredoc_line(t_heredoc **heredoc_line)
{
	if (heredoc_line && *heredoc_line)
	{
		(*heredoc_line)->next = malloc(sizeof(t_heredoc));
		if (!((*heredoc_line)->next))
			return (-1);
		*heredoc_line = (*heredoc_line)->next;
		(*heredoc_line)->next = NULL;
	}
	else
		printf("ft_add_heredoc_line: error - no heredoc_line was found\n");
	return (0);
}

// matches a heredoc line (array of strings) with the heredoc delimiter (string)
bool	ft_match_heredoc_delimiter(char **line, char *delimiter)
{
	if (!ft_strncmp(line[0], delimiter, ft_strlen(line[0] + 1))) // very basic version, for testing
	{
		if (!line[1])
			return (true);
	}
	return (false);
}

// Manages the input of one heredoc:
// - mallocs a heredoc (i.e. a heredoc line list node)
// - opens a heredoc prompt
// - reads the input line by line
// - split each line into an array of strings
// - store the split of the line in a linked list node (t_heredoc),
// 		 which is itself stored in the list of redirections (t_redir/redir_list)
// - if a line split matches the heredoc delimiter, exit the prompt
void	ft_handle_heredoc_input(t_redir *redir_list)
{
	t_heredoc	*heredoc_line;
	char		*prompt;

	heredoc_line = ft_init_heredoc();
	redir_list->heredoc = heredoc_line;
	prompt = ft_prompt(REDIR_HEREDOC);
	while (prompt != NULL)
	{
		ft_malloc_heredoc_line(&heredoc_line);
		heredoc_line->contents = ft_split_heredoc_line(prompt);
		if (ft_match_heredoc_delimiter(heredoc_line->contents, redir_list->str))
			break ; // need logic here
		prompt = ft_prompt(REDIR_HEREDOC);
	}
}

// The main heredoc input function
// goes through each command and the command's list of redirections
// if a redirection is a heredoc, calls ft_handle_heredoc_input
void	ft_open_heredocs(t_command *cmd_list)
{
	t_redir	*redir_list;
	while (cmd_list)
	{
		redir_list = cmd_list->redir_list;
		while (redir_list)
		{
			if (redir_list->type == REDIR_HEREDOC && redir_list->str_type == WORD) // {'<<', 'file.txt'}, {'<<', 'EOF1'}, {'<<', 'EOF2'}
				ft_handle_heredoc_input(redir_list);
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
}
