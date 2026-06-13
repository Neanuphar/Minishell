/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/11 19:45:49 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int boolen;

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
			break;
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
	char *new_PWD;
	char *old_PWD;

	if (argv[1] == NULL)
		chdir(getenv("HOME"));
	else
	{
		old_PWD = getcwd(NULL, 0);
		cd_update_pwd(shell, old_PWD, 1);
		if (chdir(argv[1]) == -1)
			return(free(old_PWD), 1);
		new_PWD = getcwd(NULL, 0);
		cd_update_pwd(shell, new_PWD, 0);
		free(old_PWD);
		free(new_PWD);
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

int	builtin_export(char **argv, t_shell *shell)
{
	int i;
	int j;
	char *var;

	j = 0;
	if (argv[1] == NULL)
		export_print(shell);
	else
	{
		if (ft_strchr(argv[1], '=') == NULL)
			return (env_add(shell, argv[1]), 0);
		j = ft_strchr(argv[1], '=') - argv[1];
		var = ft_substr(argv[1], 0, j);
		i = env_find(shell->envp, var);
		free (var);
		if (i != -1)
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup(argv[1]);
		}
		else
			env_add(shell, argv[1]);
	}
	return (0);
}
