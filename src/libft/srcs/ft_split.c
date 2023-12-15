/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:18:20 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/10 14:31:33 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * It counts the number of words in a string
 * 
 * @param str The string to be split.
 * @param c the character to split the string by
 * 
 * @return The number of words in the string.
 */
static int	count_words(const char	*str, char c)
{
	size_t	countw;
	size_t	i;

	countw = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != c && str[i] != 0)
		{
			countw++;
			while (str[i] != c && str[i] != 0)
				i++;
		}
		else if (str[i] != 0)
			i++;
	}
	return (countw);
}

/**
 * It copies a string from a given start index to a given end index
 * 
 * @param dst the destination string
 * @param src the string to be split
 * @param start the index of the first character to copy
 * @param last the last index of the string to copy
 */
void	ft_strcpy_split(char *dst, const char *src, int start, int last)
{
	int	i;

	i = 0;
	while (start < last)
	{
		dst[i] = src[start];
		i++;
		start++;
	}
	dst[i] = 0;
}

/**
 * This function frees the memory allocated to the 2D array of strings.
 * 
 * @param memry This is the pointer to the array of pointers.
 * @param aux This is the number of lines in the file.
 * 
 * @return A pointer to a char.
 */
static void	*freemmory(char **memry, size_t aux)
{
	size_t	i;

	i = 0;
	while (i < aux)
	{
		free(memry[i]);
		i++;
	}
	free(memry);
	return (NULL);
}

/**
 * It takes a string, a character, and a pointer to a pointer to a character, and
 * it saves the words in the string into the pointer to a pointer to a character
 * 
 * @param s the string to be split
 * @param c the character to split the string by
 * @param str the array of strings that will be returned
 */
static void	save_words(const char *s, char c, char **str)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && s[i] != 0)
		{
			start = i;
			while (s[i] != c && s[i] != 0)
				i++;
			str[j] = (char *)malloc(sizeof(char) * (i - start + 1));
			if (str[j] == 0)
			{
				freemmory(str, j);
				return ;
			}
			ft_strcpy_split(str[j], s, start, i);
			j++;
		}
		else if (s[i] != 0)
			i++;
	}
}

/**
 * It splits a string into words, separated by a character.
 * 
 * @param s The string to be split.
 * @param c the character to split the string by
 * 
 * @return A pointer to a pointer to a char.
 */
char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	n;

	if (s == 0)
		return (0);
	n = count_words(s, c);
	str = ((char **)malloc(sizeof(char *) * (n + 1)));
	if (str == 0)
		return (0);
	str[n] = 0;
	if (n == 0)
		return (str);
	save_words(s, c, str);
	return (str);
}
