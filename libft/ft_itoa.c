/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:42:23 by crtorres          #+#    #+#             */
/*   Updated: 2022/09/28 12:26:01 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

/**
 * It returns the number of digits in the number passed to it
 * 
 * @param nb the number to be converted
 * 
 * @return The length of the number.
 */
static size_t	ft_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

/**
 * It takes an integer and returns a string representation of that integer
 * 
 * @param n the number to be converted
 * 
 * @return A pointer to a string.
 */
char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	long int	i;

	len = ft_len(n);
	i = n;
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (0);
	if (i < 0)
	{
		str[0] = '-';
		i = -i;
	}
	if (i == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (i)
	{
		str[len] = i % 10 + '0';
		len--;
		i = i / 10;
	}
	return (str);
}
/*
int	main(void)
{
	int	i = 0;
	int tab[5] = {-2147483648, -42, 0, 42, 2147483647};

	while (i < 5)
		printf("%s\n", ft_itoa(tab[i++]));
	return 0;
}
*/