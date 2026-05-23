/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:04:05 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:28:39 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief cherche une sous-chaine dans une chaine avec une limite
 * 
 * @param str la chaine dans laquelle chercher
 * @param to_find la sous-chaine a chercher
 * @param len nombre maximum de caracteres a examiner
 * @return char* pointeur vers le debut de la sous-chaine ou NULL
 */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	find_len;

	if (to_find[0] == '\0')
		return ((char *)str);
	find_len = ft_strlen(to_find);
	i = 0;
	while (i < len && str[i] != '\0')
	{
		if (i + find_len > len)
			return (NULL);
		j = 0;
		while (j < find_len && str[i + j] == to_find[j])
			j++;
		if (j == find_len)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
