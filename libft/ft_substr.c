/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:06:56 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:29:25 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief extrait une sous-chaine dune chaine de caractere
 * 
 * @param s la chaine source
 * @param start lindice de debut de la sous-chaine
 * @param len la longueur maximale de la sous-chaine
 * @return char* la sous-chaine creee ou NULL si echec dallocation
 */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*dest;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

/* int main(void)
{
	char *str = "i just want this part #############";
		size_t size = 20;
		char *ret = ft_substr(str, 5, size);

		if (!strncmp(ret, str + 5, size))
		{
				free(ret);
				printf("success");
				return (0);
		}
		free(ret);
		printf("failed");
		return (0);
} */