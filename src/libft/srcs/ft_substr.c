/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:46:30 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:32:46 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * "ft_substr() returns a pointer to a new string which is a substring of the
 * string 's' starting at index 'start' and of length 'len'."
 * 
 * The first thing we do is check if the string 's' is NULL. If it is, we return
 * NULL
 * 
 * @param s The string to be cut.
 * @param start the index of the first character to include in the substring.
 * @param len the length of the substring
 * 
 * @return A pointer to a new string.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	leng;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	leng = ft_strlen(start + s);
	if (leng < len)
		len = leng;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (s + start), len + 1);
	return (str);
}
/*
int	main(void)
{
	char	*var = "abcdef";
	char	buffer[6] = "";

	printf("%s\n", strncpy(buffer, &var[2], 3));
	printf("%s\n", strcpy(buffer, &var[2]));
	var = ft_substr("abcdef", 2, 3);
	printf("%s\n", var);
	free(var);
	var = ft_substr("abcdef", 1, 2);
	printf("%s\n", var);
	free(var);

	char *s = ft_substr("tripouille", 0, 42000);
	printf(s);
	free(s);
	return (0);
}
*/