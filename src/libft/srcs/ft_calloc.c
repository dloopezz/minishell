/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:30:27 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:24:02 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * It allocates memory for an array of count elements of size bytes each and
 * returns a pointer to the allocated memory. The memory is set to zero.
 * 
 * @param count The number of elements to be allocated.
 * @param size The size of the memory block, in bytes.
 * 
 * @return A pointer to the allocated memory.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count >= SIZE_MAX)
		return (NULL);
	ptr = malloc (size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
// void	*ft_calloc(size_t count, size_t size){ return(calloc(count, size));}
/*
int main(void)
{
	printf("%p\n", SIZE_MAX);
	return(0);
}*/