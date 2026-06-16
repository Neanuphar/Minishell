/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 05:15:05 by moidoubi          #+#    #+#             */
/*   Updated: 2026/06/16 03:22:10 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *append_char(char *result, char *letter)
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

char *expand_word(char *argv, t_shell *shell)
{
	int i;
	int len_var;
	char *var;
	char *letter;
	char *result;

	i = 0;
	len_var = 0;
	result = ft_strdup("");
	while (argv[i])
	{
		if(argv[i] == 36 && (var = search_var(&argv[i + 1])) != NULL)
		{
			len_var = ft_strlen(var);
			result = handle_dollar(result, var, shell);
			i += len_var;
		}
		else
		{
			letter = ft_substr(argv, i, 1);
			result = append_char(result, letter);
		}
		i++;
	}	
	return(result);
}

int count(char **argv)
{
	int i;
	
	i = 0;
	while(argv[i])
		i++;
	return (i);
}

// char *expand_word(char *argv, t_shell *shell)
// {
// 	int i;
// 	int j;
// 	int k;
// 	int l;
// 	char *var;
// 	char *result;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	result = (char *)malloc(sizeof(ft_strlen(argv) * 2 + 1));
// 	while (argv[i])
// 	{
// 		if(argv[i] == 36 && (var = search_var(&argv[i + 1], shell)) != NULL)
// 		{
// 			i++;
// 			k = ft_strlen(var) + 1;
// 			l = env_find(shell->envp, var);
// 			while(shell->envp[l][k])
// 				result[j++] = shell->envp[l][k++];
// 		}
// 		else
// 			result[j++] = argv[i++]; 
// 	}
// 	return (result);



	// int i;
	// int j;
	// char *var;
	// char *new;
	// char *result;

	// i = 0;
	// j = 0;
	// while (argv[i])
	// {
	// 	if(argv[i] == 36)
	// 	{
	// 		i++;
			
	// 		while(argv[i] != 32 && argv[i] != '\0' && (argv[i] < 7 || argv[i] > 13))
	// 		{
	// 			new[j] = argv[i];
	// 			i++;
	// 			j++;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		new[j] = argv[i];
	// 		i++;
	// 		j++;
	// 	}
	// }
	// i = 0;
	// return (NULL);









	
// char *del_quote(char *argv, char *new)
// {
// 	int j;
// 	int k;

// 	j = 0;
// 	k = 0;
// 	while(argv[j])
// 	{
// 		if(argv[j] == 39 ||  argv[j] == 34)
// 			j++;
// 		else
// 		{
// 			new[k] = argv[j];
// 			k++;
// 			j++;
// 		}
// 	}
// 	new[k] = '\0';
// 	return (new);
// }
