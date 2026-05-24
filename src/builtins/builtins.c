/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/25 00:04:14 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(char **argv)
{
	if (argv[1] == NULL)
		return (ft_putchar_fd('\n', 1), 0);
	if (argv[1][0] == '-' && argv[1][1] == 'n')
		echo_print(argv, 2);
	else
	{
		echo_print(argv, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	(void)argv;
	(void)shell;
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
	(void)argv;
	(void)shell;
	return (0);
}
