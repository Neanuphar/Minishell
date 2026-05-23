/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:49:38 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:28:55 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief cherche la derniere occurrence dun caractere dans une chaine
 * 
 * @param s la chaine dans laquelle chercher
 * @param c le caractere a chercher
 * @return char* pointeur vers la derniere occurrence ou NULL si non trouve
 */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;

	p = s + ft_strlen(s);
	while (p >= s)
	{
		if (*p == (char)c)
			return ((char *)p);
		p--;
	}
	return (NULL);
}

/*

int main (void)
{
   const char * str = "Ma chaine de caracteres !";
   char * p = NULL;

   p = strrchr (str, 'c');

   if (p != NULL)
   {
		printf ("%s\n", p);
   }

   return (0);
}*/