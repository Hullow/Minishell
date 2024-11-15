/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pathname.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:38 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/12 16:23:18 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHNAME_H
# define PATHNAME_H

# include "Minishell.h"

typedef struct s_token	t_token;

void	ft_pathname_expansion(t_token **tokens);
int		ft_is_pathname_expansion_needed(char *value);
char	**ft_expand_pathname(char *pattern);
int		ft_match_pattern(const char *str, const char *pattern);
void	ft_replace_token_with_expanded_paths(t_token **token, char **expanded_paths);

#endif