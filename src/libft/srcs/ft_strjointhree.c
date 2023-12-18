/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointhree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:19:59 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/18 12:45:49 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjointhree(char *s1, char *s2, char *s3)
{
	char	*new;
	char	*aux;

/* 	printf("len-S1: %zu\n", ft_strlen(s1));
	printf("len-S2: %zu\n", ft_strlen(s2));
	printf("len-S3: %zu\n", ft_strlen(s3)); */
	if (!s1)
	{
		printf("entra\n");
		aux = ft_strjoin(s2, s3);
		return (aux);
	}
	if (!s3)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1));
	aux = ft_strdup(new);
	aux = ft_strjoin(s1, s2);
	new = ft_strjoin(aux, s3);
	free (aux);
	return (new);
}

/* int main()
{
	char *str="hola ";
	char *str1="soy Cristian";
	char *str2= " como estas";
	
	printf("%s\n", ft_strjoinprueba(str, str1, str2));
} */