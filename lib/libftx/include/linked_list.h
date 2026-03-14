/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:31:44 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/01 20:27:18 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "libft.h"

typedef struct s_node
{
	void			*data;
	size_t			index;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_dlist
{
	t_node			*head;
	t_node			*tail;
	size_t			size;
}					t_dlist;

t_dlist	*ft_dlist_initi(void);
t_node	*ft_new_node(void *data);
t_node	*ft_detach(t_dlist *lst, t_node *node_to_detach);

int		ft_push_node_back(t_dlist *lst, t_node *to_add);
int		ft_push_node_front(t_dlist *lst, t_node *to_add);
t_node	*ft_get_node_at(t_dlist *lst, size_t index);
int		ft_insert_node_at(t_dlist *lst, t_node *node, size_t index);

void	ft_destroy_dlst(t_dlist **lst, void (*del)(void*));

int		ft_lst_push_back(t_dlist *lst, void *content);
int		ft_lst_push_front(t_dlist *lst, void *content);
#endif
