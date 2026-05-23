/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:03:14 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/24 00:41:00 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int  run_builtin(char *cmd, char **argv, t_shell *shell)
{
    if (ft_strncmp(cmd, "echo", 5) == 0)
        return(builtin_echo(argv));
    if (ft_strncmp(cmd, "cd", 3) == 0)
        return(builtin_cd(argv, shell));
    if (ft_strncmp(cmd, "pwd", 4) == 0)
        return(builtin_pwd());
    if (ft_strncmp(cmd, "export", 7) == 0)
        return(builtin_export(argv, shell));
    if (ft_strncmp(cmd, "unset", 6) == 0)
        return(builtin_unset(argv, shell));
    if (ft_strncmp(cmd, "env", 4) == 0)
        return(builtin_env(shell));
    if (ft_strncmp(cmd, "exit", 5) == 0)
        return(builtin_exit(argv, shell));
    return (0);
}

int  is_builtin(char *cmd)
{   
    if (ft_strncmp(cmd, "echo", 5) == 0)
        return (1);
    if (ft_strncmp(cmd, "cd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "pwd", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "export", 7) == 0)
        return (1);
    if (ft_strncmp(cmd, "unset", 6) == 0)
        return (1);
    if (ft_strncmp(cmd, "env", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "exit", 5) == 0)
        return (1);
    return (0);
}
