/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 23:54:29 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/25 21:04:09 by aakli            ###   ########.fr       */
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

int	env_find(char **envp, char *key)
{
	int	i;

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

char	**env_add(t_shell *shell, char *entry)
{
	int		len;
	int		i;
	char	**new_tab;

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
	return (new_tab);
}

void	export_print(t_shell *shell)
{
	char	**copy;
	int		len;
	int		i;

	len = 0;
	while (shell->envp[len])
		len++;
	copy = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		copy[i] = shell->envp[i];
		i++;
	}
	copy[len] = NULL;
	sort_envp_copy(copy, len);
	i = 0;
	while (copy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(copy[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	free(copy);
}

void	cd_update_pwd(t_shell *shell, char *PWD, int boolen)
{
	int	i;

	if (boolen == 1)
	{
		i = env_find(shell->envp, "OLDPWD");
		if (i != -1)
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strjoin("OLDPWD=", PWD);
		}
	}
	else
	{
		i = env_find(shell->envp, "PWD");
		if (i != -1)
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strjoin("PWD=", PWD);
		}
	}
}
