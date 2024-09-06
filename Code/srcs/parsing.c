/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:26:30 by francis           #+#    #+#             */
/*   Updated: 2024/09/06 18:37:05 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

void	ft_print_token_type(struct token *head)
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

// checks if the token only contains an operator
// if so, assigns the correct operator token type
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


///// ATTEMPT TO IMPLEMENT Recursive Decent Parsing
/////
// typedef enum {command, cmd_name, cmd_word, cmd_prefix, cmd_suffix} Symbol;
// To parse our string using the grammar (see Tokenization-and-parsing####Minishell_grammar)
// if we are attempting to match e.g. a "command" symbol (left-hand side),
// e.g. for the string: grep hello
// => tokenization: 'grep', 'hello' 
// for *cmd_prefix cmd_word cmd_suffix*:
	// what do we check for "cmd_prefix" ? "grep" or "grep hello"
	// it's minimum 3 tokens, so it cannot be can only be a subset by definition, so we remove two

	// e.g. for the string: find . -name "hello"
	// cmd_prefix => find .
/* struct token	*ft_parse_using_grammar(struct token *head)
{

	// Example:
	// 
	ft_parse_pipe_sequence
	{
		if (ft_parse_command != NULL)
		{
			// To implement later:
				// string satisfies definition of "cmd_prefix cmd_word cmd_suffix"
				// string satisfies definition of "cmd_prefix cmd_word"
				// string satisfies definition of "cmd_prefix"

			// string satisfies definition of "cmd_name cmd_suffix"
			if (ft_parse_command_name != NULL)
			// string satisfies definition of "cmd_name"
			else if (ft_parse_command_name != NULL)

			else
				return NULL;
		}
		// else if (ft_parse_pipe_sequence != NULL)
		// {

		// }
		else
			return NULL;
	}
} */

/* ft_parse_command_suffix(struct token *tok)
{
// io_redirect
// 		=> TO IMPLEMENT

// | cmd_suffix io_redirect
// 		=> TO IMPLEMENT

// |            WORD
	if (tok)
		tok->type = WORD;
	
// | cmd_suffix WORD
// 		=> TO IMPLEMENT
}

ft_parse_command_name(struct token *tok)
{
	if (ft_strchr(tok->str, '=') == NULL)
		tok->type = WORD;
	else	
		return (NULL); // should be 7b : ft_parse_command_word(tok);
	return (tok);
} */

struct command	*ft_assign_command_sequence(struct token *head)
{
	struct command	*cmd_sequence;
	int				i;
	struct token	*tkn;

	cmd_sequence = malloc (sizeof(struct command));
	if (!cmd_sequence)
		return (NULL);
	i = 0;
	tkn = head;
	if (tkn->type == WORD)
	{
		cmd_sequence->cmd_name = ft_strdup(tkn->str);
		i = ft_count_token_list_args(tkn);
		if (i == 1)
		{
			cmd_sequence->args = malloc((2) * sizeof(char *));
			if (!cmd_sequence->args)
				return (NULL); // call error function ?
			cmd_sequence->args[0] = ft_strdup(tkn->str);
			cmd_sequence->args[1] = NULL;
		}
		else
		{
			tkn = tkn->next;
			cmd_sequence->args = malloc((i + 1) * sizeof(char *));
			if (!cmd_sequence->args)
				return (NULL); // call error function ?
			i = 0;
			while (tkn)
			{
				// printf("parsing - tkn->type: %d\n", tkn->type);
				if (tkn->type == WORD)
				{
					// printf("tkn->str: {%s}\n", tkn->str);
					cmd_sequence->args[i] = ft_strdup(tkn->str);
					// printf("parsing - arg %d: %s\n", i, cmd_sequence->args[i]);
					if (cmd_sequence->args[i] == NULL)
						return (NULL);
				}
				i++;
				tkn = tkn->next;
			}
			cmd_sequence->args[i] = NULL;
			i = 0;
			while (cmd_sequence->args[i])
			{
				// printf("parsing - cmd->args: %s\n", cmd_sequence->args[i]);
				i++;	
			}
		}
	}
	return (cmd_sequence);
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