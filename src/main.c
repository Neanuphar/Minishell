/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/13 22:52:34 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

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

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_node *ast;
	char *readed;
	
	(void)argc;
	(void)argv;
	shell.envp = envp_dup(envp);
	shell.exit_code = 0;
	shell.running = 1;
	while (1)
	{
		readed = readline("minishell>>");
		if (!readed)
			break;
		add_history(readed);
		ast = bridge(readed);
		execute_ast(ast, &shell);
		free_ast(ast);
		free(readed);
	}
	return (0);
}