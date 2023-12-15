/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:56:23 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/09 12:01:21 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function `ft_strspn` calculates the length of the initial segment of
 * `str1` that consists of only characters from `str2`.
 * 
 * @param str1 A pointer to the first character of the string to be searched.
 * @param str2 str2 is a pointer to a null-terminated string that contains a
 * set of characters.
 * 
 * @return the value of the variable "count".
 */
size_t	ft_strspn(const char *str1, const char *str2)
{
	size_t count;
	const char	*ptr1;
	const char	*ptr2;

	count = 0;
	while (*str1)
	{
	    ptr1 = str1;
	    ptr2 = str2;
	    while (*ptr2 && *ptr1 != *ptr2)
			++ptr2;
	    if (*ptr2 == '\0')
			return (count);
	    ++count;
	    ++str1;
	}
	return (count);
}
