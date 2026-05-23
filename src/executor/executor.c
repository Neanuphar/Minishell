/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/23 23:56:34 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_cmd(t_node *node, t_shell *shell)
{
	(void)node;
	(void)shell;
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