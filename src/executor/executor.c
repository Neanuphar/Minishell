/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/24 23:01:33 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_cmd(t_node *node, t_shell *shell)
{
	char	**cmd;
	pid_t	pid;
	int		status;
	char	*path;

	cmd = expand_argv(node->argv, shell);
	if (cmd == NULL)
		return (1);
	if (is_builtin(node->argv[0]) == 1)
		return (run_builtin(cmd[0], cmd, shell));
	else
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
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
	}
	return (0);
}

static int	exec_pipe(t_node *node, t_shell *shell)
{
	(void)node;
	(void)shell;
	return (0);
}

static int	exec_and(t_node *node, t_shell *shell)
{
	(void)node;
	(void)shell;
	return (0);
}

static int	exec_or(t_node *node, t_shell *shell)
{
	(void)node;
	(void)shell;
	return (0);
}

int	execute_ast(t_node *node, t_shell *shell)
{
	if (node == NULL)
		return (0);
	if (node->type == NODE_CMD)
		return (exec_cmd(node, shell));
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, shell));
	if (node->type == NODE_AND)
		return (exec_and(node, shell));
	if (node->type == NODE_OR)
		return (exec_or(node, shell));
	return (0);
}