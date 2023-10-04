/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:22:55 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:26:29 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function ft_strcpy() copies the string pointed to by src, including the
 * terminating null byte ('\0'), to the buffer pointed to by dst
 * 
 * @param dst This is the destination string.
 * @param src The string to be copied.
 * 
 * @return The address of the first character of the string.
 */
static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src [i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/**
 * Ft_strdup() allocates memory for a copy of the string s, does the copy, and
 * returns a pointer to it
 * 
 * @param s The string to be copied.
 * 
 * @return A pointer to the first character of the string.
 */
char	*ft_strdup(const char *s)
{
	char	*c;

	c = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (c == NULL)
		return (NULL);
	return (ft_strcpy(c, s));
}
