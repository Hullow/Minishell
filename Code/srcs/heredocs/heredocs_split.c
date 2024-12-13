/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:26:22 by fallan            #+#    #+#             */
/*   Updated: 2024/12/13 01:38:11 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Minishell.h"

// Need to fix, segfaults
void	ft_print_heredocs(t_command *cmd_list)
{
	t_redir		*redir;
	t_heredoc 	*heredoc_line;
	int			i = 0;
	int			j = -1;

	while (cmd_list)
	{
		redir = cmd_list->redir_list;
		while (redir)
		{
			heredoc_line = redir->heredoc;
			if (heredoc_line)
			{
				while (heredoc_line)
				{
					printf("heredoc line %d:\n", ++i);
					while (ft_strncmp((heredoc_line->contents)[++j], "", 1))
						printf("{%s}  ", (heredoc_line->contents)[j]);
					printf("\n");
					j = -1;
					heredoc_line = heredoc_line->next;
				}
			}
			i = 0;
			redir = redir->next;
		}
		cmd_list = cmd_list->next;
	}
}

// counts the number of strings our split should contain
int	ft_calc_heredoc_line_size(char const *s)
{
	int	prev;
	int	i;
	int	count;

	prev = -1;
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			if (i - prev - 1 > 0)
				count++;
			prev = i;
		}
		i++;
	}
	if (i - prev - 1 > 0)
		count++;
	return (count);
}

// copies a split string
int	ft_add_heredoc_line_splitted(char const *s, int start, int end, char **ret)
{
	*ret = ft_substr(s, start + 1, end - start - 1);
	if (*ret == NULL)
		return (0);
	return (1);
}

// while over the whole string to split it, by calling ft_add_splitted, if we
// encounter the splitting characters ' ' (space) or '\t' (tab)
int	ft_apply_heredoc_line_split(char const *s, char **ret)
{
	int	prev;
	int	i;

	prev = -1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			if (i - prev - 1 > 0)
			{
				if (!ft_add_heredoc_line_splitted(s, prev, i, ret))
					return (0);
				ret++;
			}
			prev = i;
		}
		i++;
	}
	if (i - prev - 1 > 0)
	{
		if (!ft_add_heredoc_line_splitted(s, prev, i, ret))
			return (0);
	}
	return (1);
}

// Splits a line of a heredoc into an array of strings, 
// Like ft_split, but only splits for spaces (' ') and tabs ('\t')
char	**ft_split_heredoc_line(char const *str)
{
	char	**ret;
	size_t	size;
	int		i;

	size = ft_calc_heredoc_line_size(str);
	ret = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	if (!ft_apply_heredoc_line_split(str, ret))
	{
		i = 0;
		while (ret[i] != NULL)
		{
			free(ret[i]);
			i++;
		}
		free(ret);
		return (NULL);
	}
	return (ret);
}


/*
// FOR UNIT TESTING

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (start > strlen(s))
		return (strdup(""));
	if (start + len > strlen(s))
		len = strlen(s) - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// ft_split_heredoc_contents tester
int main (int argc, char **argv)
{
	int	i = 0;
	int	j = -1;
	char	**ret;

	while (argv[++i])
	{
		ret = ft_split_heredoc_contents(argv[i]);
		if (ret)
		{
			printf("Splitting:\n");	
			while (ret[++j])
				printf("{%s}-", ret[j]);
			printf("\n");
		}
		j = -1;
	}
	ret = ft_split_heredoc_contents("ZZZZ		\n		OOOOOOOOO");
	{
		printf("Splitting:\n");	
		while (ret[++j])
			printf("{%s}-", ret[j]);
		printf("\n");
	}
	return (0);
}
*/