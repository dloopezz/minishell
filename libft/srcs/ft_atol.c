/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:28:58 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 15:40:20 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long int	ft_atol(char *str)
{
	long int	number;
	long int	sign;

	number = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\r' \
		|| *str == '\n' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (sign * number);
}
