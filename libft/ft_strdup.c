/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:27:17 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:27:13 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief duplique une chaine de caractere en allouant de la memoire
 * 
 * @param src la chaine a dupliquer
 * @return char* pointeur vers la nouvelle chaine ou NULL si echec
 */
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*tab;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(src);
	tab = malloc(sizeof(*tab) * (size + 1));
	if (tab == NULL)
		return (NULL);
	while (i < size)
	{
		tab[i] = src[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "salut oui cava je suis 42";

	printf("%s\n", ft_strdup(str));
	return (0);
}*/