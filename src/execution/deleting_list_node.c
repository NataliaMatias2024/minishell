/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting_list_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:41:02 by namatias          #+#    #+#             */
/*   Updated: 2026/02/14 14:53:01 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	deleteting_all_nodes(t_environment **head);

void	deleting_node(t_environment *to_delete)
{
	if (!to_delete)
		return ;
	if (to_delete->value)
	{
		free(to_delete->value);
		to_delete->value = NULL;
	}
	if (to_delete->variable)
	{
		free(to_delete->variable);
		to_delete->variable = NULL;
	}
	free(to_delete);
}

static void	deleteting_all_nodes(t_environment **head)
{
	t_environment	*current_node;
	t_environment	*temp;

	if (!head || !*head)
		return ;
	current_node = (*head);
	while (current_node)
	{
		temp = current_node->next;
		deleting_node(current_node);
		current_node = temp;
	}
}

void	deleting_list(t_environment **head)
{
	if (!head || !*head)
		return ;
	deleteting_all_nodes(head);
	*head = NULL;
}
