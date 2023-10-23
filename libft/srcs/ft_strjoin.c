/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:30:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/20 14:20:28 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * It takes two strings, and returns a new string that is the 
 * concatenation of the two strings
 * 
 * @param s1 The first string to be joined.
 * @param s2 The string to be appended to the end of s1.
 * 
 * @return A pointer to a new string that is the concatenation of s1 and s2.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new_string;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1 || !s2)
	{
		new_string = ft_strdup(s1);
		return (free(s1), free(s2), new_string);
	}
	new_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!new_string)
		return (NULL);
	while (s1[++i])
		new_string[i] = s1[i];
	while (s2[++j])
		new_string[i + j] = s2[j];
	new_string[i + j] = '\0';
	return (new_string);
}
