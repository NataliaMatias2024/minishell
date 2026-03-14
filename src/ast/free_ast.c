/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:36:19 by namatias          #+#    #+#             */
/*   Updated: 2026/03/09 20:49:51 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *head)
{
	t_redir	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head->next;
		free(head->file);
		free(head);
		head = temp;
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_cmd(t_ast *node)
{
	free_argv(node->arg);
	free_redir(node->redir_lst);
	free(node);
}

void	free_pipe(t_ast *node)
{
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == ND_PIPE)
		free_pipe(node);
	else if (node->type == ND_CMD)
		free_cmd(node);
}
