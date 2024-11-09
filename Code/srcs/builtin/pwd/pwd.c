/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:22:59 by cmegret           #+#    #+#             */
/*   Updated: 2024/11/09 11:52:12 by cmegret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/Minishell.h"

void	ft_pwd(t_shell_state *shell_state)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		shell_state->last_exit_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	shell_state->last_exit_status = 0;
}
