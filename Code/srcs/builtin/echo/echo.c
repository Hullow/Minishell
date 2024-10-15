/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:43:16 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/14 15:46:21 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

void ft_echo(char **args)
{
    int i = 0;

    while (args[i])
    {
        ft_printf("%s", args[i]);
        if (args[i + 1])
            ft_printf(" ");
        i++;
    }
    ft_printf("\n");
}
