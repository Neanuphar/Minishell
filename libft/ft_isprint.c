/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 06:13:54 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:16:11 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief verifie si le int c est bien un caractere imprimable 
 * 
 * @param c le caractere a verifier
 * @return int si cest le cas retourne 1 sinon 0
 */
int	ft_isprint(int c)
{
	if ((c >= 32 && c <= 126))
		return (1);
	return (0);
}
