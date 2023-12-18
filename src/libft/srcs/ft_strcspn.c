/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:19:45 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/16 18:02:37 by dlopez-s         ###   ########.fr       */
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
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
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