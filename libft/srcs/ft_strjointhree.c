/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointhree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:19:59 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/20 14:27:12 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjointhree(char *s1, char *s2, char *s3)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = -1;
	if (!s1 && !s2 && !s3)
		return (NULL);
	else if (!s1 || !s2)
		return (new = ft_strdup(s1), free(s1), free(s2), new);
	else if (!s3)
		ft_strjoin(s1, s2);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 2));
	if (!new)
		return (NULL);
	if (s1 && s2)
		new = ft_strjoin(s1, s2);
	while (new[i])
		i++;
	while (s3[++j])
		new[i + j] = s3[j];
	return (new[i + j] = '\0', new);
}
/* int main()
{
	char *str="hola ";
	char *str1="soy Cristian";
	char *str2= " como estas";
	
	printf("%s\n", ft_strjoinprueba(str, str1, str2));
} */