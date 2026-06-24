/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/24 07:57:07 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_argv(char **argv, t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;
	char	**new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (count(argv) + 1));
	if (new == NULL)
		return (NULL);
	while (argv[i])
	{
		tmp = expand_word(argv[i], shell);
		if (!tmp || (!tmp[0] && !ft_strchr(argv[i], 39) && !ft_strchr(argv[i],
					34)))
			free(tmp);
		else
			new[j++] = tmp;
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	*expand_heredoc(char *argv, t_shell *shell)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (argv[i])
	{
		if (argv[i] == 36)
			result = handle_dollar_in_str(argv, &i, result, shell);
		else
			result = append_char(result, ft_substr(argv, i, 1));
		i++;
	}
	return (result);
}
