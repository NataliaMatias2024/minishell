/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 12:02:20 by mkitano           #+#    #+#             */
/*   Updated: 2026/03/01 16:43:16 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_pipe_nd(t_node *pipe, t_node *start, t_node *end)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = ND_PIPE;
	node->left = build_ast(start, pipe->prev);
	node->redir_lst = NULL;
	node->arg = NULL;
	if (!node->left)
	{
		free(node);
		return (NULL);
	}
	node->right = build_ast(pipe->next, end);
	if (!node->right)
	{
		free_ast(node->left);
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast	*create_cmd_nd(t_node *start, t_node *end)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = ND_CMD;
	node->left = NULL;
	node->right = NULL;
	node->arg = fill_arg(start, end);
	node->redir_lst = extr_redir(start, end);
	return (node);
}
