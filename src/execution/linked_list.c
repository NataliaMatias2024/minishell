/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:41:01 by namatias          #+#    #+#             */
/*   Updated: 2026/02/11 15:38:39 by namatias         ###   ########.fr       */
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

t_environment	*detach_node(t_environment **head, t_environment *target)
{
	t_environment	*temp_prev;
	t_environment	*temp;
	
	if (!*head || !head || !target)
		return (NULL);
	temp = *head;
	temp_prev = NULL;
	while (temp)
	{
		if (temp == target)
		{
			//se o targe for o primeiro item da lista
			if(temp_prev == NULL)
				*head = temp->next;
			else
				temp_prev->next = temp->next; //o next do prev será igual ao next do nosso target
			temp->next = NULL;
			// target = temp;
			return (temp);
		}
		temp_prev = temp;
		temp = temp->next;
	}
	return (NULL);
}

void	print_list(t_environment *head)
{
	t_environment	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->variable, temp->value);
		temp = temp->next;
	}
}
