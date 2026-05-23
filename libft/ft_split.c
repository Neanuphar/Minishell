/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:44:05 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:30:49 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief separe une chaine en tableau de chaines selon un delimiteur
 * 
 * @param s la chaine a separer
 * @param c le caractere delimiteur
 * @return char** le tableau de chaines resultant ou NULL si echec
 */
#include "libft.h"

size_t	c_words(char const *s, char c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

void	free_split(char **tab, size_t i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (c_words(s, c) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			len = word_len(s, c);
			dest[i++] = ft_substr(s, 0, len);
			if (!dest[i - 1])
				return (free_split(dest, i - 1), NULL);
			s += len;
		}
	}
	dest[i] = NULL;
	return (dest);
}
/* int	main(void)
{
	char	*string;
	char	**result;
	int		i;

	string = "      split       this for   me  !       ";
	result = ft_split(string, ' ');
	i = 0;
	while (result[i])
	{
		printf("[%s]\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
} */
