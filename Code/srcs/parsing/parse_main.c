/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:35:29 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/19 16:09:38 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

struct s_token *ft_parse_command(struct s_token *token_seq);
struct s_token *ft_parse_cmd_name_and_suffix(struct s_token *token_seq);
struct s_token *ft_parse_cmd_name(struct s_token *token_seq);
struct s_token *ft_parse_cmd_suffix(struct s_token *token_seq, \
int tokens_to_evaluate);

struct s_token	*ft_parse_operators(struct s_token *head)
{
	struct s_token	*iterator;

	iterator = head;
	while (iterator)
	{
		if (!(iterator->type))
		{
			if (!(ft_strncmp(iterator->str, ">", 2)))
				iterator->type = REDIR_OUTPUT;
			else if (!(ft_strncmp(iterator->str, "<", 2)))
				iterator->type = REDIR_INPUT;
			else if (!(ft_strncmp(iterator->str, ">>", 3)))
				iterator->type = REDIR_APPEND;
			else if (!(ft_strncmp(iterator->str, "<<", 3)))
				iterator->type = REDIR_HEREDOC;
			else if (!(ft_strncmp(iterator->str, "|", 2)))
				iterator->type = PIPE;
		}
		iterator = iterator->next;
	}
	return (head);
}

static int	ft_allocate_single_arg(struct s_token *tkn,
	struct s_command *cmd_sequence)
{
	cmd_sequence->args = malloc(2 * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1); // call error function ?
	cmd_sequence->args[0] = ft_strdup(tkn->str);
	cmd_sequence->args[1] = NULL;
	return (0);
}

static int	ft_allocate_multiple_args(struct s_token *tkn,
	struct s_command *cmd_sequence, int arg_count)
{
	int	i;

	cmd_sequence->args = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd_sequence->args)
		return (-1); // call error function ?
	cmd_sequence->args[0] = ft_strdup(tkn->str);
	tkn = tkn->next;
	i = 1;
	while (tkn)
	{
		if (tkn->type == WORD || tkn->type == SUFFIX)
		{
			cmd_sequence->args[i] = ft_strdup(tkn->str);
			if (cmd_sequence->args[i] == NULL)
				return (-1);
			i++;
		}
		tkn = tkn->next;
	}
	cmd_sequence->args[i] = NULL;
	return (0);
}

static int	ft_process_args(struct s_token *tkn, struct s_command *cmd_sequence)
{
	int	arg_count;

	arg_count = ft_count_token_list_args(tkn);
	if (arg_count == 1)
	{
		if (ft_allocate_single_arg(tkn, cmd_sequence) == -1)
			return (-1);
	}
	else
	{
		if (ft_allocate_multiple_args(tkn, cmd_sequence, arg_count) == -1)
			return (-1);
	}
	return (0);
}

// OLD VERSION (before ft_parse_command, etc. use)
//
// Parses our linked list of tokens, starting from left (head)
// Extracts the command and the arguments 
// Outputs a struct command with the command name and the arguments
struct s_command	*ft_parse_old(struct s_token *head)
{
	struct s_command	*cmd_sequence;
	struct s_token		*tkn;

	cmd_sequence = malloc(sizeof(struct s_command));
	if (!cmd_sequence)
		return (NULL);
	tkn = head;
	if (tkn->type == WORD)
	{
		cmd_sequence->cmd_name = ft_strdup(tkn->str);
		if (ft_process_args(tkn, cmd_sequence) == -1)
			return (NULL); // call error function ?
	}
	return (cmd_sequence);
}

struct s_command	*ft_parse(struct s_token *head)
{
	struct s_command	*cmd_sequence;
	struct s_token		*tkn;

	cmd_sequence = malloc(sizeof(struct s_command));
	if (!cmd_sequence)
		return (NULL);
	tkn = head;
	ft_parse_command(tkn);
	ft_tokenization_checker(tkn);
	if (tkn->type == WORD)
		cmd_sequence->cmd_name = ft_strdup(tkn->str);
	if (ft_process_args(tkn, cmd_sequence) == -1)
			return (NULL); // call error function ?
	return (cmd_sequence);
}

/*
Simplified grammar to implement:
command   		 : cmd_name cmd_suffix
                 | cmd_name
                 ;

cmd_name         : WORD

cmd_suffix       : 			  WORD
                 | cmd_suffix WORD
*/

// We do not implement (for now):
// 	- pipes parsing: we start at "command" in the grammar
// 	- '=' : so no rules 7a+7b, and only cmd_name, no cmd_word
// 	- io_redirect
// 	- cmd_prefix


// To parse: `ls -la`
// 	=> before using these functions, we got
// "string: {ls} – token type: WORD
// string: {-la} – token type: WORD" => why ?
// 
// `ls` is executed without the `-la` option 

// grammar rule  implemented:
// command   		: cmd_name cmd_suffix
//                  | cmd_name
//                  ;
struct s_token *ft_parse_command(struct s_token *token_seq)
{
	if (ft_parse_cmd_name(token_seq))
	{
		printf("parsed cmd_name\n");
		return (token_seq);
	}
	else if (ft_parse_cmd_name_and_suffix(token_seq))
	{
		printf("parsed cmd_name_and_suffix\n");
		return (token_seq);
	}
	else
		return (NULL);
	return (token_seq);
}

// grammar rule  implemented
// 		cmd_name         : WORD
struct s_token *ft_parse_cmd_name(struct s_token *token_seq) // add lookahead ?
{
	if (token_seq == NULL) // no token => cannot parse, return NULL
		return (NULL);
	else if (token_seq->str && token_seq->next == NULL) // if there is a string and there is no further token
		token_seq->type = WORD; // match, we assign type WORD and return the token
	else
	{
		printf("ft_parse_cmd_name: token followed by another token/token string not found, returning NULL\n");
		return (NULL);
	}
	return (token_seq);
}

// grammar rule implemented
// 		command   		 : cmd_name cmd_suffix
struct s_token *ft_parse_cmd_name_and_suffix(struct s_token *token_seq)
{
	if (token_seq->next) // if there is another token
	{
		if (token_seq->str) // if there is a string and there is no further token
			token_seq->type = WORD;
		else
			return (NULL);
		if (ft_parse_cmd_suffix(token_seq->next, ft_count_token_list_args(token_seq) - 1) != NULL)
		{
			printf("ft_parse_cmd_and_suffix successful\n");
			return (token_seq);
		}
		else
		{
			printf("ft_parse_cmd_name_and_suffix: ft_parse_cmd_name and/or ft_parse_cmd_suffix couldn't parse, returning NULL\n");
			return (NULL);
		}
	}
	else // if there is only one token
	{
		printf("ft_parse_cmd_name_and_suffix: only found one token, returning NULL\n");
		return (NULL);
	}
	return (token_seq);
}

// This function parses command suffix symbols, 
// useful for input like `cp file1.txt file2.txt file3.txt /destination/directory/`
//
// grammar rule  implemented
//
// 		cmd_suffix	: 			  WORD
//  				| cmd_suffix  WORD
struct s_token *ft_parse_cmd_suffix(struct s_token *token_seq, \
int tokens_to_evaluate)
{
	struct s_token *iterator;
	int				i;

	iterator = token_seq;
	if (!token_seq)
		return (NULL);
	if (!token_seq->next)
		return (NULL);
	if (token_seq && token_seq->str && token_seq->next == NULL) // WORD
	{
		token_seq->type = SUFFIX; // SUFFIX use: for testing purposes
		printf("\nft_parse_cmd_suffix: assigned SUFFIX to %s\n", token_seq->str);
	}
	printf("ft_parse_cmd_suffix: tokens to evaluate: %d\n", tokens_to_evaluate);
	i = 0;
	if (token_seq->next && token_seq->str) // cmd_suffix WORD (iteration + some recursion)
	{
		while (++i < tokens_to_evaluate) // iteration: goes to the end of the cmd_suffix sequence to parse
		{
			iterator = iterator->next; // (this can be the last token in the linked list, or not)
			if (iterator)
				printf("ft_parse_cmd_suffix: iterator: %s\n", iterator->str);
		}
		if (iterator && iterator->str) // if we find a str at the end,
		{
			printf("ft_parse_cmd_suffix: iterator at the end: assigning WORD to %s\n", iterator->str);
			iterator->type = SUFFIX; // assign it the type WORD (SUFFIX use: for testing purposes)
		}
		else
		{
			printf("ft_parse_cmd_suffix: last token has no string or an empty token string, returning NULL\n");
			return (NULL);
		}
	}
	else
	{
		printf("ft_parse_cmd_suffix: , returning NULL\n");
		return (NULL);
	}
	tokens_to_evaluate--;
	if (tokens_to_evaluate) // if there are tokens left to evaluate to the right (avoids infinite loop)
	{
		printf("calling ft_parse_cmd_suffix again\n");
		ft_parse_cmd_suffix(token_seq, tokens_to_evaluate); // parse cmd_suffix again
	}
	return (token_seq);
}
