/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:29:53 by namatias          #+#    #+#             */
/*   Updated: 2026/03/09 19:26:03 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exec_fork(t_exec *exec, t_ast *node);

int	execute_commands_handler(t_exec *exec, t_ast *node, int in_pipe)
{
	if (!exec || !node)
		return (1);
	if (is_builtin_command(exec, node->arg))
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
	return (0);
}

static	void	exec_fork(t_exec *exec, t_ast *node)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	status = 0;
	exit_code = 0;
	pid = fork();
	if (pid < 0)
		perror("minishell: fork fail");
	else if (pid == 0)
	{
		set_signals_default();
		if (node->redir_lst && apply_all_redirections(exec, node->redir_lst))
		{
			printf("checa");
			exit(1);
		}
		else
		{
			printf("pre checa");
			exec_external_command(exec, node->arg);
		}
	}
	else if (pid > 0)
	{
		//TODO retirar após teste
		int i = 0;
		printf("Arg do node:\n");
		while (node->arg[i])
		{
			printf("%s", node->arg[i]);
			i++;
		}
		printf("\n");

		set_signals_executing();
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		exec->exit_status = exit_code;
		set_signals_interactive();
	}
}
