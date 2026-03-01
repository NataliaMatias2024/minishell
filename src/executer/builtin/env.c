/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:59:49 by namatias          #+#    #+#             */
/*   Updated: 2026/02/19 02:55:43 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list(t_env **head);

int	builtin_env(t_env **head, char **args)
{
	if (!head)
		return (1);
	else if (args[0] && args[1])
	{
		ft_putstr_fd("minishell: env: '", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd("': No such file or directory", STDERR_FILENO);
		return (127);
	}
	else
		print_list(head);
	return (0);
}

static void	print_list(t_env **head)
{
	t_env	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->value != NULL)
			printf("%s=%s\n", temp->variable, temp->value);
		temp = temp->next;
	}
}
