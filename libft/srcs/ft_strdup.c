/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:22:55 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/10 14:33:30 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
