/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 06:46:17 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:30:28 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief cherche un caractere dans une zone memoire
 * 
 * @param s pointeur vers la zone memoire
 * @param c le caractere a chercher
 * @param n nombre doctets a examiner
 * @return void* pointeur vers le caractere trouve ou NULL
 */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	uc;

	p_s = (unsigned char *)s;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*p_s == uc)
			return ((void *)p_s);
		p_s++;
	}
	return (NULL);
}
/*
int main (void)`
{
   char * str = "Une S de caracteres !";
   char * ret = NULL;

   ret = ft_memchr (str, 'd', 12);
   printf ("ret = %s\n", ret);

   return (0);
}*/