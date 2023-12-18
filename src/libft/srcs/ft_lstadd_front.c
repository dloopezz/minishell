/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:00:57 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:25:06 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * The function adds a new node to the front of a linked list.
 * 
 * @param lst The parameter `lst` is a pointer to a pointer to the first node 
 * of a linked list. It is a double pointer because we want to modify the 
 * pointer to the first node of the list if we add a new node to the front of 
 * the list.
 * @param new The new node that needs to be added to the front of the 
 * linked list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}
