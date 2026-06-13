/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/03 20:56:17 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

// int	main(void)
// {
// 	return (0);
// }

static char	**envp_dup(char **envp)
{
	int		len;
	int		i;
	char	**copy;

	len = 0;
	while (envp[len])
		len++;
	copy = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	test_echo(char **args, t_shell *shell)
{
	t_node	node;

	node.type = NODE_CMD;
	node.argv = args;
	node.redirs = NULL;
	node.left = NULL;
	node.right = NULL;
	execute_ast(&node, shell);
}

// ----------- test echo complet -----------

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*a1[2];
	char	*a2[3];
	char	*a3[3];
	char	*a4[3];
	char	*a5[5];
	char	*a6[4];
	char	*a7[4];

	(void)argc;
	(void)argv;
	shell.envp = envp_dup(envp);
	shell.exit_code = 0;
	shell.running = 1;
	a1[0] = "echo"; a1[1] = NULL;
	a2[0] = "echo"; a2[1] = "-n"; a2[2] = NULL;
	a3[0] = "echo"; a3[1] = "-nnnn"; a3[2] = NULL;
	a4[0] = "echo"; a4[1] = "-nx"; a4[2] = NULL;
	a5[0] = "echo"; a5[1] = "-n"; a5[2] = "-n"; a5[3] = "hi"; a5[4] = NULL;
	a6[0] = "echo"; a6[1] = "hi"; a6[2] = "-n"; a6[3] = NULL;
	a7[0] = "echo"; a7[1] = "hello"; a7[2] = "world"; a7[3] = NULL;
	ft_putstr_fd("1) echo        : [", 1);
	test_echo(a1, &shell);
	ft_putstr_fd("]  attendu: [newline]\n", 1);
	ft_putstr_fd("2) echo -n     : [", 1);
	test_echo(a2, &shell);
	ft_putstr_fd("]  attendu: []\n", 1);
	ft_putstr_fd("3) echo -nnnn  : [", 1);
	test_echo(a3, &shell);
	ft_putstr_fd("]  attendu: []\n", 1);
	ft_putstr_fd("4) echo -nx    : [", 1);
	test_echo(a4, &shell);
	ft_putstr_fd("]  attendu: [-nx newline]\n", 1);
	ft_putstr_fd("5) echo -n -n hi:[", 1);
	test_echo(a5, &shell);
	ft_putstr_fd("]  attendu: [hi]\n", 1);
	ft_putstr_fd("6) echo hi -n  : [", 1);
	test_echo(a6, &shell);
	ft_putstr_fd("]  attendu: [hi -n newline]\n", 1);
	ft_putstr_fd("7) echo hello world:[", 1);
	test_echo(a7, &shell);
	ft_putstr_fd("]  attendu: [hello world newline]\n", 1);
	return (0);
}
