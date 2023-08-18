/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:12:00 by crtorres          #+#    #+#             */
/*   Updated: 2022/09/29 18:58:45 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It returns a pointer to the last occurrence of the character c in the string
 * str.
 * 
 * @param str This is the string to be searched.
 * @param c The character to search for.
 * 
 * @return The address of the last occurrence of the character c 
 * in the string str.
 */
char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
			i--;
	}
	return (0);
}
