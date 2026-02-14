/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/13/02 17:26:53 by mkitano           #+#    #+#             */
/*   Created: 2026/13/02 17:40:51 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

int	ft_lst_push_back(t_dlist *lst, void *content)
{
	t_node	*node;

	if (!lst)
		return (0);
	node = ft_new_node(content);
	if (!node)
		return (0);
	return (ft_push_node_back(lst, node));
}