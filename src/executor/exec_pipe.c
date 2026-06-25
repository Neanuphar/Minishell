/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:35:45 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/25 09:25:47 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_left(t_node *node, t_shell *shell, int *pipefd)
{
	int status;
	
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	status = execute_ast(node->left, shell);
	close(1);
	exit(status);
}

void	fork_right(t_node *node, t_shell *shell, int *pipefd)
{
	int status;

	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	status = execute_ast(node->right, shell);
	close(0);
	exit(status);
}
