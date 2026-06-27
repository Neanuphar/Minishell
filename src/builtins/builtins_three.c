/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 20:18:05 by aakli             #+#    #+#             */
/*   Updated: 2026/06/25 23:26:29 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(const char *id)
{
	int	i;

	if (!id || id[0] == '\0')
		return (0);
	if (!ft_isalpha(id[0]) && id[0] != '_')
		return (0);
	i = 1;
	while (id[i])
	{
		if (!ft_isalnum(id[i]) && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_no_value(char *arg, t_shell *shell)
{
	(void)shell;
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	cd_dash(t_shell *shell, char *old_pwd)
{
	char	*oldpwd_val;
	int		i;

	i = env_find(shell->envp, "OLDPWD");
	if (i == -1)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		free(old_pwd);
		return (1);
	}
	oldpwd_val = shell->envp[i] + 7;
	if (chdir(oldpwd_val) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(oldpwd_val, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(old_pwd);
		return (1);
	}
	ft_putendl_fd(oldpwd_val, 1);
	return (0);
}

int	cd_classic(char *arg, char *old_pwd)
{
	if (chdir(arg) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(old_pwd);
		return (1);
	}
	return (0);
}

void	sort_envp_copy(char **copy, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
			{
				tmp = copy[j];
				copy[j] = copy[j + 1];
				copy[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
