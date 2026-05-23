/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:43:32 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/24 00:49:58 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			builtin_unset(char **argv, t_shell *shell)
{
    (void)argv;
    (void)shell;
    return(0);
}

int			builtin_env(t_shell *shell)
{
    (void)shell;
    return(0);
}

int			builtin_exit(char **argv, t_shell *shell)
{
    (void)argv;
    (void)shell;
    return(0);
}