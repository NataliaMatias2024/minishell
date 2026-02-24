/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:29:53 by namatias          #+#    #+#             */
/*   Updated: 2026/02/24 18:52:39 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exec_fork(t_env *env_list, char **cmd_args);

void	execute_handler(t_env *env_list, char **cmd_args)
{
	//EXECUÇÃO DE BUILT-INS
	if (is_builtin_command(&env_list, cmd_args))
		exec_builtin(env_list, cmd_args);
	else
	{
		exec_fork(env_list, cmd_args);
	}
}

static	void	exec_fork(t_env *env_list, char **cmd_args)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid < 0)
		perror("minishell: fork fail");
	else if (pid == 0) //processo filho
	{
		//EXECUÇÃO COMANDOS EXTERNOS
		exec_external_command(env_list, cmd_args);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		exit_code = WEXITSTATUS(status);
		//printf("exit code (executor.c) = %d\n", exit_code);
	}
}
