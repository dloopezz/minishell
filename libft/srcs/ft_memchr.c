/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:39:12 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:25:46 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function ft_memchr() locates the first occurrence of c (converted to an
 * unsigned char) in string s
 * 
 * @param str This is the pointer to the block of memory where the search is
 * performed.
 * @param c The character to search for.
 * @param n The number of bytes to be searched.
 * 
 * @return The address of the first occurence of the character c in the 
 * string str.
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)str)[i]) == (unsigned char)c)
			return ((unsigned char *)str + i);
			i++;
	}
	return (0);
}
