/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/16 03:17:02 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_argv(char **argv, t_shell *shell)
{
	int i;
	int j;
	char *tmp;
	char **new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (count(argv) + 1));
	if (new == NULL)
		return (NULL);
	while(argv[i])
	{
		tmp = expand_word(argv[i], shell);
		if (!tmp || !tmp[0])
			free(tmp);
		else
			new[j++] = tmp;
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	*expand_heredoc(char *body, t_shell *shell)
{
	(void)shell;
	return (body);
}
