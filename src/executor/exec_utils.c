/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:03:14 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/25 21:01:10 by aakli            ###   ########.fr       */
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

static void	exec_child(char **cmd, t_shell *shell, t_node *node)
{
	char	*path;

	if (apply_redirs(node->redirs, shell) == -1)
		exit(1);
	path = find_path(cmd[0], shell->envp);
	if (path == NULL)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd, shell->envp);
	exit(127);
}

int	exec_extern(char **cmd, t_shell *shell, t_node *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		exec_child(cmd, shell, node);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signal();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit", 4);
			if (WCOREDUMP(status))
				write(1, " (core dumped)", 14);
		}
		write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
