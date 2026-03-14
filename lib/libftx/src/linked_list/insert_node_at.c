/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:26:53 by mkitano           #+#    #+#             */
/*   Updated: 2026/01/25 17:40:51 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

int	ft_insert_node_at(t_dlist *lst, t_node *node, size_t index)
{
	t_node	*node_at_index;

	if (!lst || !node || index > lst->size)
		return (0);
	if (index == 0)
		return (ft_push_node_front(lst, node));
	if (index == lst->size)
		return (ft_push_node_back(lst, node));
	node_at_index = ft_get_node_at(lst, index);
	node->prev = node_at_index->prev;
	node->next = node_at_index;
	node_at_index->prev->next = node;
	node_at_index->prev = node;
	lst->size++;
	return (1);
}
