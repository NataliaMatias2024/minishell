/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:41:01 by namatias          #+#    #+#             */
/*   Updated: 2026/02/14 03:54:30 by namatias         ###   ########.fr       */
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
	if (var_info)
    	new_node->value = ft_strdup(var_info);
	else
		new_node->value = NULL;
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
			if (var_info)
				temp->value = ft_strdup(var_info);
			else
				temp->value = NULL;
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
		if(temp->value != NULL)
			printf("%s=%s\n", temp->variable, temp->value);
		temp = temp->next;
	}
}

int	list_size(t_environment *head)
{
	t_environment	*temp;
	int				size;

	size = 0;
	temp = head;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}
