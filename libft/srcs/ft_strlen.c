/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:04:24 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:27:21 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * This function takes a string as a parameter and returns the length of 
 * the string
 * @param str This is the string that we are going to find the length of.
 * 
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str)
{
	unsigned long int	a;

	a = 0;
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}
/*
int	main(void)
{
	char	str[] = "42 Madrid";

	unsigned long int	count;

	count = ft_strlen(str);
	printf("%lu\n", count);
}
*/