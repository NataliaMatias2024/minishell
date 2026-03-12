/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 23:39:06 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 15:58:54 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		handle_sign_heredoc(int status, t_exec *exec);
static pid_t	set_heredoc_child(int exp, t_exec *exec, char *clean_q);

int	handle_heredoc(char *delimiter, t_exec *exec)
{
	pid_t	pid;
	int		status;
	int		expand;
	char	*clean_quotes;
	int		exit_code;

	status = 0;
	exit_code = 0;
	set_signals_ignore();
	expand = check_delimiter(delimiter);
	clean_quotes = remove_quotes(delimiter);
	pid = set_heredoc_child(expand, exec, clean_quotes);
	waitpid(pid, &status, 0);
	set_signals_interactive();
	exit_code = handle_sign_heredoc(status, exec);
	free(clean_quotes);
	return (exit_code);
}

static pid_t	set_heredoc_child(int exp, t_exec *exec, char *clean_q)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("minishell: fork");
	if (pid == 0)
	{
		set_signals_heredoc();
		create_temp_and_exec(exp, exec, clean_q);
		free (clean_q);
		free_clean_all(exec);
		if (g_signal == SIGINT)
			exit (130);
		exit (0);
	}
	return (pid);
}

static int	handle_sign_heredoc(int status, t_exec *exec)
{
	if (WIFSIGNALED(status))
	{
		exec->exit_status = 128 + WTERMSIG(status);
		return (1);
	}
	else if (WIFEXITED(status))
	{
		exec->exit_status = WEXITSTATUS(status);
		if (exec->exit_status == 130)
			return (1);
	}
	return (0);
}

int	check_and_run_heredoc(t_exec *exec, t_redir *redir)
{
	while (redir)
	{
		if (redir->kind == TK_HEREDOC)
		{
			if (handle_heredoc(redir->file, exec))
			{
				if (exec->exit_status > 128)
					unlink(".heredoc_tmp");
				else
					exec->exit_status = 1;
				return (1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

int	scan_ast_heredocs(t_exec *exec, t_ast *node)
{
	int	exit_code;

	exit_code = 0;
	if (!node || !exec)
		return (0);
	if (node->type == ND_PIPE)
	{
		if (scan_ast_heredocs(exec, node->left) == 1)
			return (1);
		if (scan_ast_heredocs(exec, node->right) == 1)
			return (1);
	}
	else if (node->type == ND_CMD)
	{
		if (node->redir_lst)
			exit_code = check_and_run_heredoc(exec, node->redir_lst);
	}
	return (exit_code);
}
