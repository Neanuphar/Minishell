/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:24:09 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:27:38 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief concatene deux chaines en creant une nouvelle chaine
 * 
 * @param s1 la premiere chaine (prefixe)
 * @param s2 la deuxieme chaine (suffixe)
 * @return char* la nouvelle chaine concatenee ou NULL si echec
 */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	total_len;
	char	*dest;

	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(total_len * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/* int main(void)
{
	char *s1 = "my favorite animal is ";
		char *s2 = s1 + 20;
		char *res = ft_strjoin(s2, s1);

		if (!strcmp(res, "s my favorite animal is "))
			{
				printf("success");
				return (0);
			}
		printf("failed");
		return (0);
} */