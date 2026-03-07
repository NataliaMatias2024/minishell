/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:52:54 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 16:51:39 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_exit_status(t_exec *exec);

void	exec_pipe(t_exec *exec, t_ast *node)
{
	int		fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fds) < 0)
		return ;
	pid_left = fork();
	if (pid_left == 0)
	{
		set_signals_default();
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec_ast(exec, node->left, 1);
		exit(exec->exit_status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		set_signals_default();
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec_ast(exec, node->right, 1);
		exit(exec->exit_status);
	}
	close(fds[0]);
	close(fds[1]);
	set_signals_executing();
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &exec->exit_status, 0);
	update_exit_status(exec); //TODO: SINAIS, TESTAR
	set_signals_interactive();
}

static void	update_exit_status(t_exec *exec)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	status = exec->exit_status;
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	exec->exit_status = exit_code;
}
