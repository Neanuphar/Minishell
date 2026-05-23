/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:37:56 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:30:34 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief copie n octets de src vers dst
 * 
 * @param dst pointeur vers la destination
 * @param src pointeur vers la source
 * @param n nombre doctets a copier
 * @return void* renvoie le pointeur dst
 */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src = src;

	p_dest = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n--)
	{
		*p_dest++ = *p_src++;
	}
	return (dest);
}
/*
int main (void)
{
   const char * str1 = "Bonjour, le monde !";
   char str2 [15] = { 0 };

   memcpy (str2, str1, 7);

   printf ("str1 : %p\n", str1);
   printf ("str2 : %p\n", str2);

   return (0);
}*/