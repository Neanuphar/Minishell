/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:43:32 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/25 21:01:42 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	if (argv[1] == NULL)
		return (0);
	i = env_find(shell->envp, argv[1]);
	if (i != -1)
	{
		free(shell->envp[i]);
		while (shell->envp[i + 1] != NULL)
		{
			shell->envp[i] = shell->envp[i + 1];
			i++;
		}
		shell->envp[i] = NULL;
	}
	return (0);
}

int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], 1);
		i++;
	}
	return (0);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	int	code;

	if (argv[1] == NULL)
	{
		free_envp(shell->envp);
		exit(shell->exit_code);
	}
	else if (argv[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	else if (is_all_num(argv[1]))
	{
		code = exit_error(argv[1]);
		free_envp(shell->envp);
		exit(code);
	}
	else
	{
		code = ft_atoi(argv[1]);
		free_envp(shell->envp);
		exit(code);
	}
	return (0);
}
