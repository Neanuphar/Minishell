/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 06:58:42 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 14:10:27 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief copie une chaine dans une autre avec une taille maximale
 * 
 * @param dst chaine de destination
 * @param src chaine source
 * @param l taille maximale de la destination
 * @return size_t la longueur totale quelle a cree
 */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t l)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (l == 0)
		return (len);
	while (src[i] != '\0' && i < l - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
