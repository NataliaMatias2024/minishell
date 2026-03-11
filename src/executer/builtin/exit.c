/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:00:38 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 14:54:49 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ft_is_valid(char *string);
static void			set_msg_error(char *args);
static long long	ft_atoll_check(char *str, long long *exit_flag);

int	builtin_exit(t_exec *exec, char **args)
{
	long long	exit_flag;

	exit_flag = 0;
	if (args[1])
	{
		if (!ft_is_valid(args[1]) || (ft_atoll_check(args[1], &exit_flag) == 1))
		{
			set_msg_error(args[1]);
			free_clean_all(exec);
			exit(2);
		}
		else if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		exit_flag = (exit_flag % 256);
		if (exit_flag < 0)
			exit_flag += 256;
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_clean_all(exec);
	exit((int)exit_flag);
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

static void	set_msg_error(char *args)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static long long	ft_atoll_check(char *str, long long *number)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if ((sign == 1 && result > 9223372036854775807ULL)
			|| (sign == -1 && result > 9223372036854775808ULL))
			return (1);
		i++;
	}
	*number = (long long)result * sign;
	return (0);
}
