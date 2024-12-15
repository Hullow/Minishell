/* #include "../../header/Minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_extract_word(char *str, int *index)
{
	int		start;
	int		len;
	char	*word;

	start = *index;
	len = 0;
	while (str[*index] && str[*index] != '$' && !ft_isspace(str[*index]))
	{
		(*index)++;
		len++;
	}
	word = ft_substr(str, start, len);
	return (word);
}
 */