/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moidoubi <moidoubi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 06:09:19 by moidoubi          #+#    #+#             */
/*   Updated: 2025/11/23 13:15:50 by moidoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief verifie si le int c est bien un caractere compris
 * 			dans le tableau ascii
 * 
 * @param c le caractere a verifier
 * @return int si cest le cas retourne 1 sinon 0
 */
int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}
