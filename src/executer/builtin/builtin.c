/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:35:08 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 16:53:35 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_command(t_exec *exec, char **args)
{
	if (!exec || !exec->env_list)
		return (0);
	if (ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "exit") == 0
		|| ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "echo") == 0
		|| ft_strcmp(args[0], "env") == 0 || ft_strcmp(args[0], "unset") == 0
		|| ft_strcmp(args[0], "export") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_exec *exec, char **args)
{
	int	status;

	if (!exec->env_list|| !args)
		return (1);
	status = 0;
	if (ft_strcmp(args[0], "pwd") == 0)
		status = builtin_pwd(exec, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		status = builtin_exit(exec, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		status = builtin_cd(exec, args);
	else if (ft_strcmp(args[0], "echo") == 0)
		status = builtin_echo(exec, args);
	else if (ft_strcmp(args[0], "env") == 0)
		status = builtin_env(exec, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		status = builtin_unset(exec, args);
	else if (ft_strcmp(args[0], "export") == 0)
		status = builtin_export(exec, args);
	return (status);
}
