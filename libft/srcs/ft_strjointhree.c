/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointhree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:19:59 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/15 16:44:48 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjointhree(char *s1, char *s2, char *s3)
{
	char *new;

	if (!s3)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	new = ft_strjoin(s1, s2);
	new = ft_strjoin(new, s3);
	return (new);
}

/* int main()
{
	char *str="hola ";
	char *str1="soy Cristian";
	char *str2= " como estas";
	
	printf("%s\n", ft_strjoinprueba(str, str1, str2));
} */