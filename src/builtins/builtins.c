/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/23 22:49:00 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	boolen;

	boolen = 0;
	i = 1;
	if (argv[1] == NULL)
		return (ft_putchar_fd('\n', 1), 0);
	while (argv[i] != NULL)
	{
		if (is_flag_n(argv[i]))
		{
			boolen = 1;
			i++;
		}
		else
			break ;
	}
	if (boolen == 1)
		echo_print(argv, i);
	else
	{
		echo_print(argv, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*new_pwd;
	char	*old_pwd;

	if (argv[1] == NULL)
		chdir(getenv("HOME"));
	else
	{
		old_pwd = getcwd(NULL, 0);
		cd_update_pwd(shell, old_pwd, 1);
		if (chdir(argv[1]) == -1)
			return (free(old_pwd), 1);
		new_pwd = getcwd(NULL, 0);
		cd_update_pwd(shell, new_pwd, 0);
		free(old_pwd);
		free(new_pwd);
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

static char	*build_new_entry(t_shell *shell, int idx, char *arg, int eq_idx)
{
	int		is_plus;
	int		name_len;
	char	*var;
	char	*joined;
	char	*entry;

	is_plus = (eq_idx > 0 && arg[eq_idx - 1] == '+');
	name_len = eq_idx - is_plus;
	var = ft_substr(arg, 0, name_len);
	if (is_plus && idx != -1)
	{
		joined = ft_strjoin(shell->envp[idx] + name_len + 1, arg + eq_idx + 1);
		entry = make_entry(var, joined);
		free(joined);
	}
	else
		entry = make_entry(var, arg + eq_idx + 1);
	free(var);
	return (entry);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int		eq_idx;
	int		is_plus;
	char	*var;
	int		idx;
	char	*entry;

	if (argv[1] == NULL)
		return (export_print(shell), 0);
	if (ft_strchr(argv[1], '=') == NULL)
		return (env_add(shell, argv[1]), 0);
	eq_idx = ft_strchr(argv[1], '=') - argv[1];
	is_plus = (eq_idx > 0 && argv[1][eq_idx - 1] == '+');
	var = ft_substr(argv[1], 0, eq_idx - is_plus);
	idx = env_find(shell->envp, var);
	entry = build_new_entry(shell, idx, argv[1], eq_idx);
	free(var);
	export_store(shell, idx, entry);
	return (0);
}
