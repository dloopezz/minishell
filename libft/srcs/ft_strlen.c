/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:04:24 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/13 13:17:30 by dlopez-s         ###   ########.fr       */
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
	if (!str)
		return (0);
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