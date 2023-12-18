/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:37:13 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:25:59 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * Ft_memset() takes a pointer to a memory area, a byte value, and a size_t 
 * length, and fills the memory area with the byte value
 * 
 * @param str This is the pointer to the block of memory to fill.
 * @param c the character to fill the memory with
 * @param n the number of bytes to be set to the value c
 * 
 * @return The address of the first byte of the memory area str.
 */
void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(((unsigned char *)str)[i]) = (unsigned char)c;
		i++;
	}
	return (str);
}
