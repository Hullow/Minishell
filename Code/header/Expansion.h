/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <francis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:38 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/20 16:33:36 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "Minishell.h"

typedef struct s_token	t_token;

// Pathname expansion
void	ft_pathname_expansion(t_token **tokens);
int		ft_is_pathname_expansion_needed(char *value);
char	**ft_expand_pathname(char *pattern);
int		ft_match_pattern(const char *str, const char *pattern);
void	ft_replace_token_with_expanded_paths(t_token **token, char **expanded_paths);

// Exit status expansion ($?)
char	*expand_exit_status(char *arg, int last_exit_status);

// Parameter expansion
// => see parameter_expansion.c

#endif