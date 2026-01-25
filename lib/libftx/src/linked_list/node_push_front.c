/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_push_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:26:53 by mkitano           #+#    #+#             */
/*   Updated: 2026/01/25 17:40:51 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

int	ft_push_node_front(t_dlist *lst, t_node *to_add)
{
	if (!lst || !to_add)
		return (0);
	to_add->prev = NULL;
	to_add->next = lst->head;
	if (lst->size == 0)
		lst->tail = to_add;
	else
		lst->head->prev = to_add;
	lst->head = to_add;
	lst->size++;
	return (1);
}
