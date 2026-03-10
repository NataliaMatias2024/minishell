/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 23:39:06 by namatias          #+#    #+#             */
/*   Updated: 2026/03/09 23:26:39 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(char *delimiter, t_exec *exec)
{
	pid_t	pid;
	int		status;
	int		expand;
	char	*clean_quotes;

	set_signals_ignore();
	expand = check_delimiter(delimiter);
	clean_quotes = remove_quotes(delimiter);
	pid = fork();
	if (pid == 0)
	{
		set_signals_heredoc();
		create_temp_and_exec(expand, exec, clean_quotes);
		free (clean_quotes);
		free_clean_all(exec);
		exit (0);
	}
	waitpid(pid, &status, 0);
	set_signals_interactive();
	if (WIFSIGNALED(status))
	{
		exec->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		free(clean_quotes);
		return (1);
	}
	else if (WIFEXITED(status))
		exec->exit_status = WEXITSTATUS(status);
	free(clean_quotes);
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
				if (exec->exit_status == 130)
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
