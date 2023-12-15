/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 08:13:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:26:41 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function ft_strlcat() appends the null-terminated string src to the end of
 * dst. It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the
 * result
 * 
 * @param dst The destination string.
 * @param src The string to be appended.
 * @param size the size of the destination buffer
 * 
 * @return The length of the string that was copied.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	c;
	size_t	d;

	len = ft_strlen(src);
	c = 0;
	while (dst[c] && c < size)
		c++;
	d = 0;
	while (src[d] && c + d + 1 < size)
	{
		dst[c + d] = src[d];
		d++;
	}	
	if (d != 0)
		dst[c + d] = '\0';
	return (len + c);
}
