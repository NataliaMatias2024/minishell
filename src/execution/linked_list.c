/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:41:01 by namatias          #+#    #+#             */
/*   Updated: 2026/02/07 01:51:30 by namatias         ###   ########.fr       */
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

void	create_update_list_env(t_environment **head, char *var, char *var_info)
{
	t_environment	*temp;

	if (!head || !var)
		return ;
	if (!*head)
	{
		*head = create_environment_node(var, var_info);
		return ;
	}
	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->variable, var) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(var_info);
			return ;
		}
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	temp->next = create_environment_node(var, var_info);
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
