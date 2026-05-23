/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:38:24 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 14:15:06 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief cherche la premiere occurrence dun caractere dans une chaine
 * 
 * @param s la chaine dans laquelle chercher
 * @param c le caractere a chercher
 * @return char* pointeur vers la premiere occurrence ou NULL si non trouve
 */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p = s;

	while (*p != (char)c)
	{
		if (*p == 0)
		{
			return (NULL);
		}
		p++;
	}
	return ((char *)p);
}
/*
int main (void)
{
   const char * str = "Ma chaine de caracteres !";
   char * p = NULL;

   p = ft_strchr (str, 'c');

   if (p != NULL)
   {
		printf ("%s\n", p);
   }

   return (0);
}*/