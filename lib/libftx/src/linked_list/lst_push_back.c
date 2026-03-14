/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:26:53 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/19 02:24:26 by namatias         ###   ########.fr       */
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
