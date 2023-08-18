/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:32:08 by crtorres          #+#    #+#             */
/*   Updated: 2022/09/28 17:32:46 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/**
 * The function ft_strchr() locates the first occurrence of c (converted to a 
 * char) in the string pointed to by s
 * 
 * @param str This is the string to be searched.
 * @param c The character to search for.
 * 
 * @return A pointer to the first occurrence of the character c in the 
 * string str.
 */
char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (const char)c)
			return ((char *) str);
			str++;
	}	
	if (*str == (const char)c)
	{
		return ((char *) str);
	}
	return (0);
}
