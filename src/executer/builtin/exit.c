/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:00:38 by namatias          #+#    #+#             */
/*   Updated: 2026/02/19 02:57:56 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid(char *string);

int	builtin_exit(t_env **env, char **args)
{
	int	exit_flag;

	exit_flag = 0;
	if (args[1])
	{
		if (!ft_is_valid(args[1]))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("exit: numeric argument required.", STDERR_FILENO);
			deleting_list(env);
			exit(2);
		}
		else if (args[2])
		{
			ft_putendl_fd("exit: too many arguments.", STDERR_FILENO);
			return (1);
		}
		exit_flag = (ft_atoi(args[1]) % 256);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	deleting_list(env);
	exit(exit_flag % 256);
	return (0);
}

static int	ft_is_valid(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '-' || string[i] == '+')
		i++;
	if (!string[i])
		return (0);
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}
