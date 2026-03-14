/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:44:53 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 16:55:34 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exist_flag(t_env **head, char *str);

int	builtin_echo(t_exec *exec, char **args)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	i = 1;
	while (args[i] && exist_flag(&exec->env_list, args[i]))
	{
		flag_n = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (flag_n != 1)
		printf("\n");
	return (0);
}

static int	exist_flag(t_env **head, char *str)
{
	int	i;

	(void)*head;
	if (!str || str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
