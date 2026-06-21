/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/21 08:42:36 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (NULL);
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
	char	*tmp;
	char	*full;
	char	**dirs;
	char	*path_env;
	int		i;

	i = 0;
	path_env = get_path_env(envp);
	if (path_env == NULL)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (dirs == NULL)
		return (NULL);
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmp, cmd);
		if (access(full, X_OK) == 0)
			return (free_tab(dirs), free(tmp), full);
		free(tmp);
		free(full);
		i++;
	}
	return (free_tab(dirs), NULL);
}
