/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:31:14 by cmegret           #+#    #+#             */
/*   Updated: 2024/09/22 16:39:45 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

/**
 * @brief Prints the environment variables.
 *
 * This function iterates through the environment variables and prints each one.
 *
 * @param envp An array of environment variables.
 */
void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}
