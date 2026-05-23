/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:44:27 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:29:12 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief supprime les caracteres dun set au debut et a la fin dune chaine
 * 
 * @param s1 la chaine a trimmer
 * @param set les caracteres a supprimer
 * @return char* la nouvelle chaine trimmee ou NULL si echec
 */
#include "libft.h"

static int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	i;
	size_t	debut;
	size_t	fin;

	debut = 0;
	while (s1[debut] && ft_char_in_set(s1[debut], set))
		debut++;
	fin = ft_strlen(s1);
	while (fin > debut && ft_char_in_set(s1[fin - 1], set))
		fin--;
	dest = (char *)malloc(sizeof(*s1) * (fin - debut + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (debut < fin)
		dest[i++] = s1[debut++];
	dest[i] = 0;
	return (dest);
}
