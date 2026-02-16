/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:41:01 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 04:55:31 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	*init_environment(char **envp)
{
	int				i;
	t_environment	*head;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		create_environment(&head, envp[i]);
		i++;
	}
	return (head);
}

void	create_environment(t_environment	**head, char *envp)
{
	size_t			index;
	char			*variable;
	char			*variable_info;
	char			*postion_equal;

	index = 0;
	while (envp[index] && envp[index] != '=')
		index++;
	postion_equal = ft_strchr(envp, '=');
	variable = ft_substr(envp, 0, index);
	if (postion_equal != NULL)
		variable_info = ft_strdup(postion_equal + 1);
	else
		variable_info = NULL;
	if (variable)
		create_update_list_env(head, variable, variable_info);
	if (variable)
		free(variable);
	if (variable_info)
		free(variable_info);
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
	while (temp->next && ft_strcmp(temp->variable, var) != 0)
		temp = temp->next;
	if (ft_strcmp(temp->variable, var) == 0)
	{
		free(temp->value);
		if (var_info)
			temp->value = ft_strdup(var_info);
		else
			temp->value = NULL;
	}
	else
		temp->next = create_environment_node(var, var_info);
}

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
