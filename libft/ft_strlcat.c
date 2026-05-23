/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 07:42:55 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:27:49 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief concatene deux chaines avec une taille maximale
 * 
 * @param dst chaine de destination
 * @param src chaine source a concatener
 * @param l taille maximale de la destination
 * @return size_t la longueur totale quelle a essaye de creer
 */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t l)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;

	src_len = ft_strlen(src);
	dest_len = 0;
	while (dest_len < l && dest[dest_len] != '\0')
		dest_len++;
	if (dest_len == l)
		return (dest_len + src_len);
	i = 0;
	while (src[i] != '\0' && (dest_len + i) < (l - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/* #include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char	*str;
	size_t	r1;
	size_t	r2;
	char	buff1[0xF00] = "there is no stars in the sky";
	char	buff2[0xF00] = "there is no stars in the sky";
	size_t	max;

	str = "the cake is a lie !\0I'm hidden lol\r\n";
	max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;
	r1 = strlcat(buff1, str, max);
	r2 = ft_strlcat(buff2, str, max);
	if (!strcmp(buff1, buff2))
	{
		printf("success");
		printf("%zu___%zu", r1, r2);
	}
	printf("fail");
	printf("%zu___%zu", r1, r2);
	return (0);
} */