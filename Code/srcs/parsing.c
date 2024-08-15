/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:26:30 by francis           #+#    #+#             */
/*   Updated: 2024/08/08 17:39:18 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

// Parses our linked list of tokens, starting from left (head)
// Extracts the command and the arguments 
// Outputs a struct command with the command name, the arguments
void	ft_tokenization_checker(struct token *head)
{
	const char *token_type_strings[9] = {
	"UNDEFINED TOKEN",
    "WORD",
    "NEWLINE",
    "REDIR_INPUT",
    "REDIR_OUTPUT",
    "REDIR_APPEND",
    "REDIR_HEREDOC",
    "PIPE",
    "END_OF_INPUT"};

	while (head)
	{
		if (head->str && head->type)
			printf("string: %s | token type: %s\n", head->str, token_type_strings[head->type]);
		else
		{
			printf("type or string not found: ");
			if (head->type)
				printf("head-type: %s, head->str not found\n", token_type_strings[head->type]);
			if (head->str)
				printf("head-str: %s, head->type not found\n", head->str);
			else
				printf("nor head->str nor head-type found\n");
		}
		head = head->next;
	}
}

struct token	*ft_parse_operators(struct token *head)
{
	struct token	*iterator;

	iterator = head;
	while (iterator)
	{
		if (!(iterator->type))
		{
			// printf("iterator->str: %s, type not found; ", iterator->str);
			if (!(ft_strncmp(iterator->str, ">", 2)))
			{	iterator->type = REDIR_OUTPUT; }	// printf("assigned type REDIR_OUTPUT"); }
			else if (!(ft_strncmp(iterator->str, "<", 2)))
			{	iterator->type = REDIR_INPUT;} //	printf("assigned type REDIR_INPUT"); }
			else if (!(ft_strncmp(iterator->str, ">>", 3)))
			{	iterator->type = REDIR_APPEND; }	// printf("assigned type REDIR_APPEND"); }
			else if (!(ft_strncmp(iterator->str, "<<", 3)))
			{	iterator->type = REDIR_HEREDOC;} //	printf("assigned type REDIR_HEREDOC"); }
			else if (!(ft_strncmp(iterator->str, "|", 2)))
			{	iterator->type = PIPE;} //printf("assigned type PIPE"); 
			// printf("\n");
		}
		iterator = iterator->next;
	}
	return (head);
}


// To parse our string and prepare for execution
// possible operations:
//	- parameter expansion
// - filename expansion (., .., )


struct command	*ft_parse(struct token *head)
{
	struct command	*cmd_sequence;
	char			**args_array;
	int				i;

	cmd = malloc (sizeof(struct command));
	if (!cmd)
		return (NULL);
	args_array = NULL;
	i = 0;
	if (head->type == WORD)
	{
		cmd->cmd_name = ft_strdup(head->str);
		head = head->next;
		if (head)
			args_array = malloc(sizeof(char **)); // CHECK MALLOC
		while (head)
		{
			if (head->type == WORD)
			{
				args_array[i] = ft_strdup(head->str);
				if (args_array[i] == NULL)
					return (NULL);
			}
			i++;
			head = head->next;
		}
		//args_array[i] = "";
		cmd->args = args_array;
	}
	return (cmd);
}

// Old version
/* struct command	*ft_parse(struct token *head)
{
	struct command	*cmd;
	char			**args_array;
	int				i;

	cmd = malloc (sizeof(struct command));
	if (!cmd)
		return (NULL);
	args_array = NULL;
	i = 0;
	if (head->type == WORD)
	{
		cmd->cmd_name = ft_strdup(head->str);
		head = head->next;
		if (head)
			args_array = malloc(sizeof(char **)); // CHECK MALLOC
		while (head)
		{
			if (head->type == WORD)
			{
				args_array[i] = ft_strdup(head->str);
				if (args_array[i] == NULL)
					return (NULL);
			}
			i++;
			head = head->next;
		}
		//args_array[i] = "";
		cmd->args = args_array;
	}
	return (cmd);
} */


/* 
// See Shell-functioning.md#Simple commands
ft_command_expansion()
{
	
} */