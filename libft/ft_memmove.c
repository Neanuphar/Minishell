/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:00:27 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:30:37 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief copie n octets de src vers dst meme si les zones se chevauchent
 * 
 * @param dst pointeur vers la destination
 * @param src pointeur vers la source
 * @param n nombre doctets a copier
 * @return void* renvoie le pointeur dst
 */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src = src;

	p_dest = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (p_src <= p_dest)
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n--)
		{
			*p_dest-- = *p_src--;
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
/*
int main (void)
{
   char tab1 [] = "abcdefghijklmno";

   printf ("tab1 = %s\n", tab1);
   memmove (tab1 + 5, tab1 + 2, 7);
   printf ("tab1 = %s\n", tab1);

   return (0);
}*/