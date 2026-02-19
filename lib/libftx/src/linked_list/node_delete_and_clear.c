/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_delete_and_clear.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:28:40 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/19 02:23:55 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

static void	ft_delete_one(t_node *to_delete, void (*del)(void*))
{
	if (!to_delete)
		return ;
	if (del)
		del(to_delete->data);
	free(to_delete);
}

static void	ft_clear_all_nodes(t_dlist *lst, void (*del)(void*))
{
	t_node	*current;
	t_node	*temp_next;

	if (!lst)
		return ;
	current = lst->head;
	while (current)
	{
		temp_next = current->next;
		ft_delete_one(current, del);
		current = temp_next;
	}
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
}

void	ft_destroy_dlst(t_dlist **lst, void (*del)(void*))
{
	if (!*lst || !lst)
		return ;
	ft_clear_all_nodes(*lst, del);
	free(*lst);
	*lst = NULL;
}
