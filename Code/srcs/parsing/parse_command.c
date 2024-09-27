/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:08:33 by fallan            #+#    #+#             */
/*   Updated: 2024/09/26 18:13:46 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"



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

// ft_parse_command : grammar rule implemented:
// command   		: cmd_name cmd_suffix
//                  | cmd_name
//                  ;


/*
Simplified grammar to implement:
command   		 : cmd_name cmd_suffix
                 | cmd_name
                 ;

cmd_name         : WORD

cmd_suffix       : 			  WORD
                 | cmd_suffix WORD
*/

struct s_token *ft_parse_command(struct s_token *token_seq)
{
	if (ft_parse_cmd_name(token_seq) && ft_parse_cmd_suffix(token_seq->next, ft_count_tokens(token_seq->next)))
	{
		printf("parsed cmd name and cmd_suffix\n");
		return (token_seq);
	}
	else if (ft_parse_cmd_name(token_seq))
	{
		printf("parsed cmd_name\n");
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
	else if (token_seq->str) // if there is a string and there is no further token
		token_seq->type = WORD; // match, we assign type WORD and return the token
	printf("\nft_parse_cmd_name: assigned WORD to %s\n", token_seq->str);
	return (token_seq);
}

/* cmd_suffix       : 			  WORD
            		| cmd_suffix  WORD
					  cmd_suffix  WORD WORD
					  cmd_suffix  WORD WORD WORD
					*/


struct s_token *ft_return_last_token(struct s_token *token_seq)
{
	if (!token_seq)
		return (NULL);
	if (!(token_seq->next))
		return (token_seq);
	while (token_seq->next)
		token_seq = token_seq->next;
	return (token_seq);
}

struct s_token *ft_io_here_doc(struct s_token *token_seq)
{
	if (!token_seq)
		return (NULL);
	if (!(token_seq->next))
		return (NULL);
	if (!(token_seq->str) || !(token_seq->next->str))
		return (NULL);
	if (token_seq->type == REDIR_HEREDOC)
		printf("ft_io_here_doc: input must be redirected from a here-document %s\n", token_seq->next->str); // call appropriate redirection function
	else
		return (NULL);
	return (token_seq);
}

struct s_token *ft_io_number(struct s_token *token_seq)
{
	if (!token_seq)
		return (NULL);
	if (!(token_seq->str))
		return (NULL);
	token_seq->type = IO_NUMBER;
	return (token_seq);
}

struct s_token *ft_io_redirect(struct s_token *token_seq)
{
	if (!token_seq)
		return (NULL);
	if (!(token_seq->next))
		return (NULL);
	if (!(token_seq->str) || !(token_seq->next->str))
		return (NULL);
	if (!(ft_io_file(token_seq)))
		return (NULL);
	else if (!(ft_io_number(token_seq) && ft_io_file(token_seq->next)))
		return (NULL);
	else if (!(ft_io_here_doc(token_seq)))
		return (NULL);
	else if (!(ft_io_number(token_seq) && ft_io_here_doc(token_seq->next)))
		return (NULL);
	return (token_seq);
}


/* io_file       : '<'			filename
                 | '>'			filename
                 | REDIR_APPEND	filename
                 */
struct s_token *ft_io_file(struct s_token *token_seq)
{
	if (!token_seq)
		return (NULL);
	if (!(token_seq->next))
		return (NULL);
	if (!(token_seq->str) || !(token_seq->next->str))
		return (NULL);
	if (token_seq->type == REDIR_INPUT)
		printf("ft_io_file: input must be redirected to file %s\n", token_seq->next->str); // call appropriate redirection function
	else if (token_seq->type == REDIR_OUTPUT)
		printf("ft_io_file: input must be redirected from file %s\n", token_seq->next->str); // call appropriate redirection function
	else if (token_seq->type == REDIR_APPEND)
		printf("ft_io_file: input must be appended to file %s\n", token_seq->next->str); // call appropriate redirection function
	else
		return (NULL);
	return (token_seq);
}

struct s_token *ft_parse_cmd_suffix_word(struct s_token *token_seq, int tokens_to_evaluate)
{
	int	i;

	i = 0;
	// find . -name main.c
	// tokens_to_evaluate == 3
	if (tokens_to_evaluate > 2) // cmd_suffix WORD (iteration + some recursion)
	{
		while (++i < tokens_to_evaluate) // iteration: goes to the end of the cmd_suffix sequence to parse
			iterator = iterator->next; // (this can be the last token in the linked list, or not)
		if (iterator && iterator->str) // if we find a str at the end,
			iterator->type = WORD; // assign it the type WORD (SUFFIX use: for testing purposes)
		else
			return (NULL);
		tokens_to_evaluate--;
	}
	else
		token_seq->type = WORD; // assign it the type WORD (SUFFIX use: for testing purposes)
	return (token_seq);
}



struct s_token *ft_parse_cmd_suffix(struct s_token *token_seq, int tokens_to_evaluate)
{

	if (!token_seq)
		return (NULL);
	else if (!(token_seq->str))
		return (NULL);
	else if (!(token_seq->next)) // WORD
		token_seq->type = WORD; // match, we assign type WORD and return the token
	else if (ft_parse_cmd_suffix_word(token_seq, tokens_to_evaluate))
		tokens_to_evaluate--;
	return (token_seq);
}


/////////////////////////////////
/// OLD VERSIONS OF FUNCTIONS ///
/////////////////////////////////
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


/* rule implemented:
	cmd_suffix      : 			  WORD
                    | cmd_suffix  WORD */
struct s_token *ft_parse_cmd_suffix(struct s_token *token_seq, \
int tokens_to_evaluate)
{
	struct s_token *iterator;
	int				i;

	iterator = token_seq;
	if (!token_seq)
		return (NULL);
	else if (!token_seq->next)
		return (NULL);
	else if (ft_parse_word(token_seq))
		return (token_seq);
	else if (tokens_to_evaluate && ft_parse_cmd_suffix(token_seq, tokens_to_evaluate) && ft_parse_word(token_seq->next))
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
