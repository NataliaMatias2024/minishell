/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:35:08 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 05:07:59 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_command(t_env **head, char **argv) //TODO: Ver qual struct sera passada
{
	if (!head || !*head)
		return (0);
	if (ft_strcmp(argv[0], "pwd") == 0 || ft_strcmp(argv[0], "exit") == 0
		|| ft_strcmp(argv[0], "cd") == 0 || ft_strcmp(argv[0], "echo") == 0
		|| ft_strcmp(argv[0], "env") == 0 || ft_strcmp(argv[0], "unset") == 0
		|| ft_strcmp(argv[0], "export") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_env *environment_list, char **argv) //TODO: Ver qual struct sera passada
{
	int	status;

	if (!environment_list || !argv)
		return (1);
	status = 0;
	if (ft_strcmp(argv[0], "pwd") == 0)
		status = builtin_pwd(&environment_list, argv);
	else if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(&environment_list, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = builtin_cd(&environment_list, argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = builtin_echo(&environment_list, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(&environment_list, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(&environment_list, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(&environment_list, argv);
	return (status);
}
