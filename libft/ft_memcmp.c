/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:25:42 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:30:30 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief compare deux zones memoire sur n octets
 * 
 * @param s1 premiere zone memoire
 * @param s2 deuxieme zone memoire
 * @param n nombre doctets a comparer
 * @return int difference entre les deux zones (0 si identiques)
 */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p_s1 = s1;
	const unsigned char	*p_s2 = s2;

	while (n--)
	{
		if (*p_s1 != *p_s2)
		{
			return (*p_s1 - *p_s2);
		}
		p_s1++;
		p_s2++;
	}
	return (0);
}

/*#define TAB_SIZE 4

int	main(void)
{
	unsigned char tab1[TAB_SIZE] = {'a', 'b', '\0', 'c'};
	unsigned char tab2[TAB_SIZE] = {'a', 'b', '\0', 'c'};
	unsigned char tab3[TAB_SIZE] = {'a', 'b', 'c', 'h'};
	unsigned char tab4[TAB_SIZE] = {'a', 'b', 'a', 'h'};

	printf("Test 1 : %d\n", ft_memcmp(tab1, tab2, TAB_SIZE));
	printf("Test 2 : %d\n", ft_memcmp(tab2, tab3, TAB_SIZE));
	printf("Test 3 : %d\n", ft_memcmp(tab3, tab4, TAB_SIZE));

	return (0);
}*/