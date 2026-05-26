/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 23:54:29 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/26 23:18:43 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_print(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	  env_find(char **envp, char *key)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
		{
			if (envp[i][ft_strlen(key)] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

char  **env_add(t_shell *shell, char *entry)
{
	int	len;
	int i;
	char **new_tab;

	len = 0;
	i = 0;
	while (shell->envp[len] != 0)
		len++;
	new_tab = (char **)malloc((sizeof(char *) * (len + 2)));
	while (i != len)
	{
		new_tab[i] = shell->envp[i];
		i++;
	}
	new_tab[i] = ft_strdup(entry);
	i++;
	new_tab[i] = NULL;
	free(shell->envp);
	shell->envp = new_tab;
	return(new_tab);
}

void export_print(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->envp[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(shell->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}