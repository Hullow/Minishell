/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:22:59 by cmegret           #+#    #+#             */
/*   Updated: 2024/10/14 14:25:17 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

void	ft_pwd(void)
{
    char	*cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("getcwd");
        return;
    }
    printf("%s\n", cwd);
    free(cwd);
}
