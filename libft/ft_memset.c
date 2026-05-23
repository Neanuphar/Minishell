/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:03:05 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:24:15 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief rempli une zone memoire avec un caractere de donne
 * 
 * @param s pointeur vers la zone memoire
 * @param c le caractere a attribuer
 * @param n le nombre doctet a remplir
 * @return void* renvoie le pointeur
 */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p_s;

	p_s = s;
	while (n--)
	{
		*p_s++ = c;
	}
	return (s);
}
/*
int	main(void)
{
	char tab[20] = {0};
	int i = 0;

	ft_memset(tab, 1, 5);

	for (i = 0; i < 20; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");

	return (0);
}*/