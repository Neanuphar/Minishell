/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:41:46 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/25 06:42:28 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_flag_n(char *s)
{
	int	i;

	if (s[0] != '-')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

char	*make_entry(char *name, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(name, "=");
	entry = ft_strjoin(tmp, value);
	free(tmp);
	return (entry);
}

void	export_store(t_shell *shell, int idx, char *entry)
{
	if (idx != -1)
	{
		free(shell->envp[idx]);
		shell->envp[idx] = entry;
	}
	else
	{
		env_add(shell, entry);
		free(entry);
	}
}

int	is_all_num(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] == '\0')
    	return (1);
	if (argv[0] == '-' || argv[0] == '+')
		i++;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exit_error(char *argv)
{
	char	*tmp;
	char	*msg;

	tmp = ft_strjoin("exit: ", argv);
	msg = ft_strjoin(tmp, ": numeric argument required");
	free(tmp);
	ft_putendl_fd(msg, 2);
	free(msg);
	return (2);
}
