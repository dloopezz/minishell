/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:39:03 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 15:38:13 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	aux = 0;
	while (*lst)
	{
		aux = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
	*lst = 0;
}
