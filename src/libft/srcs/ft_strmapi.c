/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:14:54 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:32:30 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * Ft_strmapi() applies the function f to each character of the string passed as
 * argument by giving its index as first argument to create a "fresh" new string
 * (with malloc(3)) resulting from the successive applications of f.
 * 
 * @param s The string to be mapped.
 * @param f a function that takes an unsigned int and a char and returns a char
 * @return A pointer to a new string.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	tmp = malloc(ft_strlen(s) + 1);
	if (tmp == 0)
		return (0);
	if (s == 0 || f == 0)
		return (0);
	while (s[i])
	{
		tmp[i] = f(i, s[i]);
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
