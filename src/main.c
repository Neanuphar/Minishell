/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/27 11:45:37 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

static char	**envp_dup(char **envp)
{
	int		len;
	int		i;
	char	**copy;

	len = 0;
	while (envp[len])
		len++;
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	shell_loop(t_shell *shell, struct termios *saved_term)
{
	t_node	*ast;
	char	*readed;

	while (1)
	{
		setup_signal();
		readed = readline("minishell>>");
		if (!readed)
			break ;
		add_history(readed);
		ast = bridge(readed);
		if (g_signal_receivd == SIGINT)
		{
			shell->exit_code = 130;
			g_signal_receivd = 0;
		}
		else
			shell->exit_code = execute_ast(ast, shell);
		free_ast(ast);
		free(readed);
		tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell			shell;
	struct termios	saved_term;

	(void)argc;
	(void)argv;
	shell.envp = envp_dup(envp);
	shell.exit_code = 0;
	shell.running = 1;
	tcgetattr(STDIN_FILENO, &saved_term);
	shell_loop(&shell, &saved_term);
	free_envp(shell.envp);
	return (0);
}
