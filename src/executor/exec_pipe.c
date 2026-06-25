/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:35:45 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/23 19:07:32 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_left(t_node *node, t_shell *shell, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	exit(execute_ast(node->left, shell));
}

void	fork_right(t_node *node, t_shell *shell, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	exit(execute_ast(node->right, shell));
}
