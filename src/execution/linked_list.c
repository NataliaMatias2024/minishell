/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:41:01 by namatias          #+#    #+#             */
/*   Updated: 2026/02/02 18:21:48 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	*create_environment_node(char *var, char *var_info)
{
	t_environment	*new_node;

	new_node = (t_environment *) malloc (sizeof(t_environment));
	if (new_node == NULL)
		return (NULL);
	new_node->variable = ft_strdup(var);
	new_node->value = ft_strdup(var_info);
	new_node->next = NULL;
	return (new_node);
}

void	create_list_env(t_environment **head, char *var, char *var_info)
{
	t_environment	*current_node;
	t_environment	*temp;

	current_node = create_environment_node(var, var_info);
	if (!*head)
	{
		*head = current_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = current_node;
}
//TODO: apagar após os testes
void	print_list_teste(t_environment *head)
{
	t_environment	*current_node;

	current_node = head;
	while (current_node != NULL)
	{
		printf("%s = %s\n", current_node->variable, current_node->value);
		current_node = current_node->next;
	}
}
