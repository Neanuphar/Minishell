/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 03:05:57 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/21 03:49:02 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count(char **argv)
{
	int i;
	
	i = 0;
	while(argv[i])
		i++;
	return (i);
}

char *handle_single_quote(char *argv, int *i, t_shell *shell)
{
	char quote;
	char *letter;
	char *result;

	(void)shell;
	result = ft_strdup("");
	quote = argv[*i];
	(*i)++;
	while (argv[*i] && argv[*i] != quote)
	{
		letter = ft_substr(argv, *i, 1);
		result = append_char(result, letter);	
		(*i)++;
	}
	return (result);
}

