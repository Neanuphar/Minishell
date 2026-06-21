/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/21 09:36:26 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_cmd(t_node *node, t_shell *shell)
{
	char	**cmd;
	int 	status;

	cmd = expand_argv(node->argv, shell);
	if (cmd == NULL)
		return (1);
	if (!cmd[0])
		return (free_tab(cmd), 0);
	if (is_builtin(node->argv[0]) == 1)
	{
		status = (apply_redirs(node->redirs, shell), run_builtin(cmd[0], cmd, shell));
		return (free_tab(cmd), status);
	}
	else
	{
		status = exec_extern(cmd, shell, node);
		return (free_tab(cmd), status);
	}
}

static int	exec_pipe(t_node *node, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid_left = fork();
	if (pid_left == -1)
		return (1);
	if (pid_left == 0)
		fork_left(node, shell, pipefd);
	pid_right = fork();
	if (pid_right == -1)
		return (1);
	if (pid_right == 0)
		fork_right(node, shell, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_ast(t_node *node, t_shell *shell)
{
	if (node == NULL)
		return (0);
	if (node->type == NODE_CMD)
		return (exec_cmd(node, shell));
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, shell));
	return (0);
}
