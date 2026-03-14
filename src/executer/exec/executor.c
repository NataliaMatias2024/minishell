/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:29:53 by namatias          #+#    #+#             */
/*   Updated: 2026/03/14 09:51:40 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exec_fork(t_exec *exec, t_ast *node);
static pid_t	set_and_exec_fork(t_exec *exec, t_ast *node);
static int		set_builtin_check(t_exec *exec, t_ast *node, int in_pipe);

int	exec_commands(t_exec *exec, t_ast *node, int in_pipe)
{
	int	exit_status;

	exit_status = 0;
	if (!exec || !node)
		return (1);
	if (is_builtin_command(exec, node->arg))
		exit_status = set_builtin_check(exec, node, in_pipe);
	else
	{
		if (in_pipe)
		{
			if (node->redir_lst
				&& apply_all_redirections(exec, node->redir_lst))
				exit(1);
			exec_external_command(exec, node->arg);
		}
		else
			exec_fork(exec, node);
	}
	return (exit_status);
}

static	int	set_builtin_check(t_exec *exec, t_ast *node, int in_pipe)
{
	if (node->redir_lst && apply_all_redirections(exec, node->redir_lst))
	{
		dup2(exec->backup_stdin, STDIN_FILENO);
		dup2(exec->backup_stdout, STDOUT_FILENO);
		return (1);
	}
	exec->exit_status = exec_builtin(exec, node->arg);
	dup2(exec->backup_stdin, STDIN_FILENO);
	dup2(exec->backup_stdout, STDOUT_FILENO);
	if (in_pipe)
	{
		free_clean_all(exec);
		exit(exec->exit_status);
	}
	return (0);
}

static	void	exec_fork(t_exec *exec, t_ast *node)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	status = 0;
	exit_code = 0;
	pid = set_and_exec_fork(exec, node);
	if (pid > 0)
	{
		set_signals_ignore();
		waitpid(pid, &status, 0);
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
	}
	exec->exit_status = exit_code;
}

static pid_t	set_and_exec_fork(t_exec *exec, t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("minishell: fork");
	else if (pid == 0)
	{
		set_signals_default();
		if (node->redir_lst && apply_all_redirections(exec, node->redir_lst))
		{
			free_clean_all(exec);
			exit(1);
		}
		else
		{
			if (!node->arg || !node->arg[0])
			{
				free_clean_all(exec);
				exit(0);
			}
			exec_external_command(exec, node->arg);
		}
	}
	return (pid);
}
