/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:44:38 by cmegret           #+#    #+#             */
/*   Updated: 2024/12/09 14:14:09 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "Minishell.h"

typedef struct s_token	t_token;

char	*expand_variables(char *str, t_shell_state *state);
void	expand_command_variables(t_command *cmd_list,
			t_shell_state *shell_state);
char	*get_expansion_var_name(char *str);
char	*ft_chartostr(char c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*handle_quotes(char *str, int *i, int *in_quotes, int *in_dquotes);
char	*handle_expansion(char *str, int *i, t_shell_state *state);

#endif