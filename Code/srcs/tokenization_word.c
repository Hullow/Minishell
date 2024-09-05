/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:23:03 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/04 09:48:40 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

// checks if previous character 
// 		was part of a word and that that word was not delimited
// rule #### 2.2.2.8. Previous character part of a word
// IF
// - previous character was part of a word
// added:
// - previous token is delimited
int	ft_previous_char_part_of_word(struct s_token *tok)
{
	if (tok->type == WORD && tok->is_delimited == false)
		return (1);
	else
		return (0);
}

int	ft_append_char_to_word(struct s_token **tok, char c)
{
	char	*temp;
	char	character[2];

	temp = ft_strdup((*tok)->str);
	character[0] = c;
	character[1] = '\0';
	(*tok)->str = ft_strjoin(temp, character);
	free(temp);
	return (1);
}

int	ft_new_word(struct s_token **tok, char c)
{
	char	character[2];

	character[0] = c;
	character[1] = '\0';
	(*tok) = ft_create_new_token(*tok);
	(*tok)->type = WORD;
	(*tok)->is_operator = false;
	(*tok)->str = ft_strdup(character);
	return (1);
}

struct s_token	*initialize_token(void)
{
	struct s_token	*tok;

	tok = malloc(sizeof(struct s_token));
	if (!tok)
		return (NULL);
	tok->next = NULL;
	tok->str = NULL;
	tok->type = 0;
	tok->is_operator = NULL;
	tok->is_delimited = false;
	return (tok);
}
