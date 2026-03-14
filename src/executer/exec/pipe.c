/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:52:54 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 21:18:53 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		update_exit_status(t_exec *exec);
static void		set_child_config(int *fds, t_exec *exec, t_ast *node);
static pid_t	handle_forks(int *fds, t_exec *exec, t_ast *node, int in_left);

void	exec_pipe(t_exec *exec, t_ast *node)
{
	int		fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fds) < 0)
		return ;
	pid_left = handle_forks(fds, exec, node, 1);
	pid_right = handle_forks(fds, exec, node, 0);
	close(fds[0]);
	close(fds[1]);
	set_signals_ignore();
	if (pid_left > 0)
		waitpid(pid_left, NULL, 0);
	if (pid_right > 0)
		waitpid(pid_right, &exec->exit_status, 0);
	update_exit_status(exec);
	set_signals_interactive();
}

static pid_t	handle_forks(int *fds, t_exec *exec, t_ast *node, int in_left)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("minishell: fork");
	else if (pid == 0)
	{
		if (in_left == 1)
		{
			dup2(fds[1], STDOUT_FILENO);
			set_child_config(fds, exec, node->left);
		}
		else
		{
			dup2(fds[0], STDIN_FILENO);
			set_child_config(fds, exec, node->right);
		}
	}
	return (pid);
}

static void	set_child_config(int *fds, t_exec *exec, t_ast *node)
{
	set_signals_default();
	close(fds[0]);
	close(fds[1]);
	exec_ast(exec, node, 1);
	free_clean_all(exec);
	exit(exec->exit_status);
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
	{
		exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
	exec->exit_status = exit_code;
}
