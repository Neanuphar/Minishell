/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:03:14 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/03 23:06:38 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_builtin(char *cmd, char **argv, t_shell *shell)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (builtin_echo(argv));
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (builtin_cd(argv, shell));
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (builtin_export(argv, shell));
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (builtin_unset(argv, shell));
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (builtin_env(shell));
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (builtin_exit(argv, shell));
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int exec_extern(char **cmd, t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;
	char	*path;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		apply_redirs(node->redirs);
		path = find_path(cmd[0], shell->envp);
		if (path == NULL)
			exit(127);
		execve(path, cmd, shell->envp);
		exit(127);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}