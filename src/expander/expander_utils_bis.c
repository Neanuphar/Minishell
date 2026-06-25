/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakli <aakli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 03:05:57 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/24 22:54:03 by aakli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	*handle_single_quote(char *argv, int *i)
{
	char	quote;
	char	*letter;
	char	*result;

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

char	*handle_dollar_in_str(char *argv, int *i, char *result, t_shell *shell)
{
	char	*var;

	var = search_var(&argv[*i + 1]);
	if (!var)
		result = append_char(result, ft_substr(argv, *i, 1));
	else
	{
		*i += ft_strlen(var);
		result = handle_dollar(result, var, shell);
	}
	return (result);
}
