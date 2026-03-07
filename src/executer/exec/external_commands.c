/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:46:12 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 03:18:19 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_external_command(t_exec *exec, char **cmd_args)
{
	char	*pathname;
	char	**envp;

	pathname = create_path_array(exec->env_list, cmd_args);
	if (!pathname)
	{
		ft_putstr_fd("minishell: Command '", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putendl_fd("' not found", STDERR_FILENO);
		free(pathname);
		exit(127);
	}
	envp = transform_env_list(exec->env_list);
	execve(pathname, cmd_args, envp);
	perror("minishell");
	free(pathname);
	free_split(envp);
	exit(126);
}
