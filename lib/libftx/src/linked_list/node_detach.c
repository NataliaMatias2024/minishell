/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_detach.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 09:57:42 by mkitano           #+#    #+#             */
/*   Updated: 2026/01/25 17:40:51 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_node	*ft_detach(t_dlist *lst, t_node *node_to_detach)
{
	if (!lst || !node_to_detach)
		return (NULL);
	if (node_to_detach->prev)
		node_to_detach->prev->next = node_to_detach->next;
	if (node_to_detach->next)
		node_to_detach->next->prev = node_to_detach->prev;
	if (lst->head == node_to_detach)
		lst->head = node_to_detach->next;
	if (lst->tail == node_to_detach)
		lst->tail = node_to_detach->prev;
	lst->size--;
	node_to_detach->next = NULL;
	node_to_detach->prev = NULL;
	return (node_to_detach);
}
