/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:43:32 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/24 09:41:44 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(char **argv, t_shell *shell)
{
	int i;

	i = env_find(shell->envp, argv[1]);
	if(i != -1)
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
	else if (argv[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return(1);
	}
	else if (is_all_num(argv[1]))
		exit(exit_error(argv[1]));
	else
	{
		code = ft_atoi(argv[1]);
		exit(code);
	}
	return(0);
}
