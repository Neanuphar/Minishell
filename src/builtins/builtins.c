/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/24 00:50:01 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			builtin_echo(char **argv)
{
    (void)argv;
    return(0);
}

int			builtin_cd(char **argv, t_shell *shell)
{
    (void)argv;
    (void)shell;
    return(0);
}

int			builtin_pwd(void)
{
    return(0);
}

int			builtin_export(char **argv, t_shell *shell)
{
    (void)argv;
    (void)shell;
    return(0);
}

