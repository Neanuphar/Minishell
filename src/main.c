/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/24 23:02:25 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

int	main(void)
{
	return (0);
}
// ------------------------teste ls --------------------
// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	shell;
// 	t_node	node;
// 	char	*args[2];

// 	(void)argc;
// 	(void)argv;
// 	args[0] = "ls";
// 	args[1] = NULL;
// 	node.type = NODE_CMD;
// 	node.argv = args;
// 	node.redirs = NULL;
// 	node.left = NULL;
// 	node.right = NULL;
// 	shell.envp = envp;
// 	shell.exit_code = 0;
// 	shell.running = 1;
// 	execute_ast(&node, &shell);
// 	return (0);
// }
