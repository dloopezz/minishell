/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:53:30 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/16 18:05:51 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * It returns 1 if the character c is in the string set, and 0 otherwise
 * 
 * @param c The character to search for in the set.
 * @param set the set of characters to be searched
 * 
 * @return the number of characters in the string that are not in the set.
 */
static int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * It returns a copy of the string s1, without any characters in set
 * 
 * @param s1 The string to be trimmed.
 * @param set the set of characters to trim
 * 
 * @return A pointer to a new string.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	len;

	start = 0;
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	len = ft_strlen(s1);
	while (len > start && ft_char_in_set(s1[len - 1], set))
		len--;
	str = (char *)malloc(sizeof(*s1) * (len - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < len)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
