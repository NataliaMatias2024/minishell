/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:50:36 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 10:41:43 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*get_and_detach_node(t_env **head, char *args);
static t_env	*detach_node(t_env **head, t_env *target);

int	builtin_unset(t_exec *exec, char **args)
{
	int		i;
	int		exit_code;
	t_env	*target_node;

	if (!args[1])
		return (0);
	i = 1;
	exit_code = 0;
	while (args[i])
	{
		target_node = get_and_detach_node(&exec->env_list, args[i]);
		if (target_node)
			deleting_node(target_node);
		i++;
	}
	return (exit_code);
}

static t_env	*get_and_detach_node(t_env **head, char *args)
{
	t_env	*temp;
	t_env	*target_node;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->variable, args) == 0)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	target_node = detach_node(head, temp);
	return (target_node);
}

static t_env	*detach_node(t_env **head, t_env *target)
{
	t_env	*temp_prev;
	t_env	*temp;

	if (!*head || !head || !target)
		return (NULL);
	temp = *head;
	temp_prev = NULL;
	while (temp)
	{
		if (temp == target)
		{
			if (temp_prev == NULL)
				*head = temp->next;
			else
				temp_prev->next = temp->next;
			temp->next = NULL;
			return (temp);
		}
		temp_prev = temp;
		temp = temp->next;
	}
	return (NULL);
}
