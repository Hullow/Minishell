/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:27:25 by fallan            #+#    #+#             */
/*   Updated: 2024/12/13 20:20:38 by francis          ###   ########.fr       */
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


// matches a heredoc line (linked list of tokens, with strings inside)
// with the heredoc delimiter (string)
bool	ft_match_heredoc_delimiter(char *heredoc_line, char *delimiter)
{
	if (!ft_strncmp(heredoc_line, delimiter, ft_strlen(heredoc_line + 1))) // very basic version, for testing
		return (true);
	return (false);
}

// mallocs the first node of our heredoc
// (which is a linked list of heredoc lines)
t_heredoc	*ft_init_heredoc(void)
{
	t_heredoc	*heredoc_line;

	heredoc_line = malloc(sizeof(t_heredoc));
	if (!heredoc_line)
		return (NULL);
	heredoc_line->line = NULL;
	heredoc_line->next = NULL;
	return (heredoc_line);
}

// mallocs a new heredoc line and sets heredoc_line address to it 
t_heredoc	*ft_malloc_new_heredoc_line(t_heredoc *heredoc_line)
{
	heredoc_line->next = malloc(sizeof(t_heredoc));
	heredoc_line = heredoc_line->next;
	if (!heredoc_line)
		return (NULL);
	heredoc_line->line = NULL;
	heredoc_line->next = NULL;
	return (heredoc_line);
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

	if (!redir_list || !redir_list->str)
		return ;
	heredoc_line = ft_init_heredoc();
	if (!heredoc_line)
		return ;
	redir_list->heredoc = heredoc_line;
	while (1)
	{
		prompt = ft_prompt(REDIR_HEREDOC);
		if (!prompt) // EOF (Ctrl+D)
		{
			printf("\n");
			break ;
		}
		if (*prompt)
		{
			heredoc_line->line = ft_strdup(prompt);
			if (ft_match_heredoc_delimiter(heredoc_line->line, redir_list->str))
			{
				free(prompt);
				break ;
			}
			heredoc_line = ft_malloc_new_heredoc_line(heredoc_line);
			if (!heredoc_line)
			{
				free(prompt);
				break ;
			}
		}
		free(prompt);
	}
}

// The main heredoc input function
// goes through each command and the command's list of redirections
// if a redirection is a heredoc, calls ft_handle_heredoc_input
void	ft_open_heredocs(t_command *cmd_list)
{
	t_redir		*redir_list;
	// t_command	*cmd_list_head;

	// cmd_list_head = cmd_list; // Save the head of the command list
	while (cmd_list)
	{
		redir_list = cmd_list->redir_list;
		while (redir_list)
		{
			if (redir_list->type == REDIR_HEREDOC && redir_list->str_type == WORD)
				ft_handle_heredoc_input(redir_list);
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
	// ft_print_heredocs(cmd_list_head); // Appel de la fonction pour imprimer le contenu des heredocs
}

// prints all heredocs in all redirection lists for all commands
void	ft_print_heredocs(t_command *cmd_list)
{
	t_redir		*redir_list;
	t_heredoc	*heredoc;

	if (!cmd_list)
		return ;
	while (cmd_list)
	{
		redir_list = cmd_list->redir_list;
		while (redir_list)
		{
			if (redir_list->type == REDIR_HEREDOC && redir_list->str_type == WORD)
			{
				heredoc = redir_list->heredoc;
				if (!heredoc)
				{
					redir_list = redir_list->next;
					continue ;
				}
				printf("Contenu du heredoc pour %s:\n", redir_list->str);
				while (heredoc)
				{
					printf("{%s}", heredoc->line);
					heredoc = heredoc->next;
				}
				printf("\n");
				}
			}
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
}
