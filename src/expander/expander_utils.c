/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 05:15:05 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/21 04:08:51 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *append_char(char *result, char *letter)
{
	char *tmp;
	
	tmp = ft_strjoin(result, letter);
	free(letter);
	free(result);
	result = tmp;
	return (result);
}

static char *handle_dollar(char *result,char *var,t_shell *shell)
{
	int j;
	char *tmp;
	
	if((j = env_find(shell->envp, var)) != -1)
	{
		tmp = ft_strjoin(result, shell->envp[j] + ft_strlen(var) + 1);
		free(result);
		free(var);
		result = tmp;
	}
	else
	{
		tmp = ft_strjoin(result, "");
		free(result);
		free(var);
		result = tmp;
	}
	return (result);
}

static char *search_var(char *str)
{
	int i;
	int j;
	char *var;
	
	i = 0;
	j = 0;
	var = (char *)malloc(ft_strlen(str) + 1);
	if (!var)
		return (NULL);
	if (str[i] == 32 || str[i] == '\0' || (str[i] >= 7 && str[i] <= 13))
		return (free(var), NULL);
	while(ft_isalnum(str[i]) || str[i] == '_')
		var[j++] = str[i++];
	if (j == 0)
		return (free(var), NULL);
	var[j] = 0;
	return (var);
}

static char *handle_double_quote(char *argv, int *i, t_shell *shell)
{
	char quote;
	char *var;
	char *letter;
	char *result;

	result = ft_strdup("");
	quote = argv[*i];
	(*i)++;
	while (argv[*i] && argv[*i] != quote)
	{
		if(argv[*i] == 36 && (var = search_var(&argv[*i + 1])) != NULL)
		{
			*i +=  ft_strlen(var);
			result = handle_dollar(result, var, shell);
		}
		else
		{
			letter = ft_substr(argv, *i, 1);
			result = append_char(result, letter);	
		}
		(*i)++;
	}
	return (result);
}

char *expand_word(char *argv, t_shell *shell)
{
	int i;
	char *var;
	char *result;

	i = 0;
	result = ft_strdup("");
	while (argv[i])
	{
		if(argv[i] == 39)
			result = append_char(result, handle_single_quote(argv, &i, shell));
		else if(argv[i] == 34)
			result = append_char(result, handle_double_quote(argv, &i, shell));
		else if(argv[i] == 36 && (var = search_var(&argv[i + 1])) != NULL)
		{
			i +=  ft_strlen(var);
			result = handle_dollar(result, var, shell);
		}
		else
			result = append_char(result, ft_substr(argv, i, 1));
		i++;
	}	
	return(result);
}
