/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:52:54 by namatias          #+#    #+#             */
/*   Updated: 2026/03/01 17:27:13 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exec_fork(t_exec *exec, char **cmd_args)
int	exec_pipe(t_exec *exec, t_ast *tree)
{
	int		fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fds) < 0)
	{
		perror("minishell: pipe");
		exec->exit_status = 1;
		return (1);
	}
	//executar fork pra direita
	pid_right = fork();
	if (pid_right == 0) //processo filho da direita
	{
		// | comandos do fork da direita
		//joga os comando de escrita (STDOUT) para o de entrada dos comandos da sua direita
		//
		dup2(fds[1], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);

	}
	//executar fork pra esquerda
	pid_left = fork();
	if (pid_left == 0) //processo filho da direita
	{
		dup2(fds[0], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
}
