/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:41:46 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/24 09:38:46 by moidoubi         ###   ########.fr       */
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

int	is_all_num(char *argv)
{
	int i;

	i = 0;
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

int exit_error(char *argv)
{
    char *tmp;
    char *msg;

    tmp = ft_strjoin("exit: ", argv);
    msg = ft_strjoin(tmp, ": numeric argument required");
    free(tmp);
    ft_putendl_fd(msg, 2);
    free(msg);
    return(2);
}