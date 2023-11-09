/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:19:45 by crtorres          #+#    #+#             */
/*   Updated: 2022/12/12 18:56:59 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function ft_strcspn() returns the number of characters in the initial
 * segment of s which consists entirely of characters not in reject
 * 
 * @param s The string to be searched.
 * @param reject The characters to search for.
 * 
 * @return The number of characters in the initial segment of s which consists
 * entirely of characters not in reject.
 */
size_t  ft_strcspn(const char *s, const char *reject)
{
	size_t	i = 0;
	size_t	j = 0;

	while (s[i])
	{
		while (reject[j])
		{
			if (reject[j] == s[i])
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

/* int	main(void)
{
	printf("%lu\n", ft_strcspn("test", "t"));
	printf("%lu\n", strcspn("test", "es"));
printf("%lu\n", ft_strcspn("test", "f"));
	printf("%lu\n", strcspn("tester", "f"));
} */