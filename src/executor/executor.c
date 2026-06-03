/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/03 21:19:43 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_cmd(t_node *node, t_shell *shell)
{
	char	**cmd;

	cmd = expand_argv(node->argv, shell);
	if (cmd == NULL)
		return (1);
	if (is_builtin(node->argv[0]) == 1)
		return (run_builtin(cmd[0], cmd, shell));
	else
		return (exec_extern(cmd, shell));
}

static int	exec_pipe(t_node *node, t_shell *shell)
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
	return (0);
}
