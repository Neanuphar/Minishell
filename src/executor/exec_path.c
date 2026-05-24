/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/05/24 22:23:00 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		else
			i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char *tmp;
	char *full;
	char **dirs;
	char *path_env;
	int i;

    i = 0;
	path_env = get_path_env(envp);
	dirs = ft_split(path_env, ':');
    while (dirs[i])
    {
        tmp = ft_strjoin(dirs[i], "/");
        full = ft_strjoin(tmp, cmd);
        if (access(full, X_OK) == 0)
            return(free_tab(dirs), free(tmp), full);
        free(tmp);
        free(full);
        i++;
    }
	return (free_tab(dirs), NULL);
}
