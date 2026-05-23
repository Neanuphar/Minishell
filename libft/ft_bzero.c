/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:32:11 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:16:32 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief met tous les octets d'une zone memoire a zero
 *
 * @param s pointeur vers la zone memoire a mettre a zero
 * @param n nombre d'octets a mettre a zero
 */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*int	main(void)
{
	char tab[20] = {0};
	int i = 0;

	bzero(tab, 5);

	for (i = 0; i < 20; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");

	return (0);
}*/