/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:41:48 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 22:02:45 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_all_redirections(t_exec *exec, t_redir *node)
{
	int	status;

	status = 0;
	while (node)
	{
		if (node->kind == REDIR_IN)
			status = handle_redir_in(node->file);
		else if (node->kind == TK_OUT)
			status = handle_redir_output(node->file);
		else if (node->kind == TK_APPEND)
			status = handle_append(node->file);
		else if (node->kind == TK_HEREDOC)
		{
			status = handle_redir_in(".heredoc_tmp");
			unlink(".heredoc_tmp");
		}
		if (status != 0)
			break ;
		node = node->next;
	}
	exec->exit_status = status;
	return (status);
}

int	handle_redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_redir_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
