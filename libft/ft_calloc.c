/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:31:21 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:15:13 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief alloue et initialise une zone memoire a zero
 * 
 * @param nmemb nombre delements a allouer
 * @param size taille de chaque element
 * @return void* pointeur vers la zone allouee ou NULL si echec
 */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	block;

	block = nmemb * size;
	if (nmemb && (size != (block / nmemb)))
		return (NULL);
	tab = malloc(nmemb * size);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
