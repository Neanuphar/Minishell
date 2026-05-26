/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:43:32 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/26 23:56:12 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(char **argv, t_shell *shell)
{
	int idx;

	idx = env_find(shell->envp, argv[1]);
	if(idx != -1)
	{
		free(shell->envp[idx]);
		while (shell->envp[idx + 1] != NULL)
		{
			shell->envp[idx] = shell->envp[idx + 1];
			idx++;
		}
		shell->envp[idx] = NULL;
	}
	return (0);
}

int	builtin_env(t_shell *shell)
{
	int i;

	i = 0;
	while(shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], 1);
		i++;
	}
	return (0);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	int code;
	
	if (argv[1] == NULL)
		exit(shell->exit_code);
	else
	{
		code = ft_atoi(argv[1]);
		exit(code);
	}
	return(0);
}
