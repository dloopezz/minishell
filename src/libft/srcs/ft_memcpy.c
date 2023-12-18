/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:44:38 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/16 18:00:36 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function copies n bytes from memory area src to memory area dst
 * 
 * @param dst The destination string.
 * @param src The source string.
 * @param n the number of bytes to copy
 * 
 * @return The address of the destination string.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	a;

	a = 0;
	if (dst == 0 && src == 0)
		return (0);
	if (src == dst)
		return (dst);
	while (a < n)
	{
		(((unsigned char *)dst)[a]) = (((unsigned char *)src)[a]);
		a++;
	}
	return (dst);
}
