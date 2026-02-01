/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:26:53 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/01 20:27:00 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_node	*ft_get_node_at(t_dlist *lst, size_t index)
{
	t_node	*current;
	size_t	i;

	if (!lst || index >= lst->size)
		return (NULL);
	if (index < lst->size / 2)
	{
		current = lst->head;
		i = 0;
		while (i++ < index)
			current = current->next;
	}
	else
	{
		current = lst->tail;
		i = lst->size - 1;
		while (i-- > index)
			current = current->prev;
	}
	return (current);
}
