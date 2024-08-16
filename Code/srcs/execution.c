/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:48:18 by francis           #+#    #+#             */
/*   Updated: 2024/08/16 12:05:59 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Minishell.h"

/* ft_execution()
{
	if (ft_has_pipe)
	{

		list commands = ft_split_pipe();
		ft_execute_pipes(commands);
	}
	else
		{
			if (ft_has_redir())
				fd = ft_execute_redir(); // redir error handling ?
			ft_execute_command(commands);
		}

}

ft_has_redir(struct token *head)
{
	while (head)
	{
		if (head->type == REDIR)
			return (1);
		head = head->next;
	}
	return (0);
} */


// Builtin checker: checks if the command corresponds to a builtin
int	ft_is_builtin(struct command *cmd)
{
	if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "export", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "env", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd->cmd_name, "exit", 4) == 0)
		return (0);
	else
		return (1);
}


char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (cmd == NULL || envp == NULL) {
		perror("cmd or envp is NULL");
		return (NULL);
	}

	paths = get_env_paths(envp);
	if (!paths)
	{
		perror("get_env_paths failed");
		return (NULL);
	}

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (!full_path)
		{
			perror("ft_strjoin failed");
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);
}

int execute_cmd(struct command *cmd, char **envp)
{
	int		pid;
	char	*cmd_path;
	int		status;

	if (cmd == NULL || envp == NULL)
		return (1);
	cmd_path = NULL;
	if (ft_is_builtin(cmd)) // if not a builtin, search
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{
			cmd_path = get_cmd_path(cmd->cmd_name, envp);
			/*	int i = 0;
				while (cmd->args[i])
					printf("cmd->args: %s\n", cmd->args[i++]);	*/
			if (cmd_path == NULL)
			{
				perror("get_cmd_path");
				exit(1);
			}
			else if (execve(cmd_path, cmd->args, envp) == -1)
			{
				perror("execve");
				free(cmd_path);
				exit(1);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			
			if (WIFEXITED(status))
			{
				//printf("Child exited with status %d\n", WEXITSTATUS(status));
				return WEXITSTATUS(status);
			}
			else
			{
				//printf("Child terminated abnormally\n");
				free(cmd_path);
				return 1;
			}
		}
	}
	return (0);
}

/*
POSIX.1-2017:
 2.12. Shell Execution Environment

A shell execution environment consists of the following:

    Open files inherited upon invocation of the shell, plus open files controlled by exec
    Working directory as set by cd
    File creation mask set by umask
    [XSI] [Option Start] File size limit as set by ulimit [Option End]
    Current traps set by trap
    Shell parameters that are set by variable assignment (see the set special built-in) or from the System Interfaces volume of POSIX.1-2017 environment inherited by the shell when it begins (see the export special built-in)
    Shell functions; see Function Definition Command
    Options turned on at invocation or by set
    Process IDs of the last commands in asynchronous lists known to this shell environment; see Asynchronous Lists
    Shell aliases; see Alias Substitution

Utilities other than the special built-ins (see Special Built-In Utilities) shall be invoked 
in a separate environment that consists of the following. 
The initial value of these objects shall be the same as that for the parent shell, except as noted below.

    Open files inherited on invocation of the shell, open files controlled by the exec special built-in plus any modifications, and additions specified by any redirections to the utility

    Current working directory

    File creation mask

    If the utility is a shell script, traps caught by the shell shall be set to the default values and traps ignored by the shell shall be set to be ignored by the utility; if the utility is not a shell script, the trap actions (default or ignore) shall be mapped into the appropriate signal handling actions for the utility

    Variables with the export attribute, along with those explicitly exported for the duration of the command, shall be passed to the utility environment variables

The environment of the shell process shall not be changed by the utility unless explicitly specified by the utility description (for example, cd and umask).

A subshell environment shall be created as a duplicate of the shell environment, except that signal traps that are not being ignored shall be set to the default action. Changes made to the subshell environment shall not affect the shell environment. Command substitution, commands that are grouped with parentheses, and asynchronous lists shall be executed in a subshell environment. Additionally, each command of a multi-command pipeline is in a subshell environment; as an extension, however, any or all commands in a pipeline may be executed in the current environment. All other commands shall be executed in the current shell environment.

*/