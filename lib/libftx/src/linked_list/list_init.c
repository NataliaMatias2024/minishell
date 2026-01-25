/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 09:57:42 by mkitano           #+#    #+#             */
/*   Updated: 2026/01/25 17:40:42 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_dlist	*ft_dlist_initi(void)
{
	t_dlist	*d_list;

	d_list = (t_dlist *)malloc(sizeof(t_dlist));
	if (!d_list)
		return (NULL);
	d_list->head = NULL;
	d_list->tail = NULL;
	d_list->size = 0;
	return (d_list);
}
