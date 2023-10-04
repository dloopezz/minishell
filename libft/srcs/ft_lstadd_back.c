/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:20:18 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:25:02 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * If the list is empty, make the new node the head of the list. Otherwise, 
 * add the new node to the end of the list
 * 
 * @param lst A pointer to the first link of a list.
 * @param new the new element to add to the list
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!ft_lstlast(*lst))
		*lst = new;
	else
		ft_lstlast(*lst)-> next = new;
}
