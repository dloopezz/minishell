/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:29:03 by crtorres          #+#    #+#             */
/*   Updated: 2022/09/29 18:59:02 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * If the first character of the substring is found in the string, then check if
 * the rest of the substring is also found in the string
 * 
 * @param str The string to be searched.
 * @param to_find the string to find
 * @param n the number of characters to be searched
 * 
 * @return A pointer to the first occurrence of the string to_find in the string
 * str, or a null pointer if the string to_find is not part of the string str.
 */
char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	c;

	if (*to_find == '\0')
		return ((char *)str);
	i = 0;
	while ((*str != '\0') && (i < n))
	{
		c = 0;
		while ((*(str + c)) == (*(to_find + c)) && (i + c < n))
		{
			if (*(to_find + c + 1) == '\0')
				return ((char *)str);
			c++;
		}
		i++;
		str++;
	}
	return (0);
}
