/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:26:53 by mkitano           #+#    #+#             */
/*   Updated: 2026/01/25 18:40:51 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

int	ft_push_node_back(t_dlist *lst, t_node *to_add)
{
	if (!lst || !to_add)
		return (0);
	to_add->next = NULL;
	to_add->prev = lst->tail;
	if (lst->size == 0)
		lst->head = to_add;
	else
		lst->tail->next = to_add;
	lst->tail = to_add;
	lst->size++;
	return (1);
}
