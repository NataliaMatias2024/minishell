/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:41:57 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/01 19:26:27 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_check(t_node *node)
{
	t_token	*token;

	if (!node || !node->data)
		return (0);
	token = (t_token *)node->data;
	if (!node->prev)
	{
		err_msg(token->lexeme);
		return (0);
	}
	if (!node->next || ((t_token *)node->next->data)->kind == TK_EOF)
	{
		err_msg("newline")
	}
	if (((t_token *)node->prev->data)->kind != TK_WORD
		|| ((t_token *)node->next->data)->kind != TK_WORD)
	{
		err_msg((t_token *)node->next->data)->lexeme);
		return (0);
	}
	return (1);
}

int redir_check(t_node *node)
{
	t_token	*next;

	if (!node || !node->next)
	{
		err_msg("newline")
		return (0);
	}
	next = (t_token *)node->next->data;
	if (!next || next->kind == TK_EOF)
	{
		err_msg("newline")
		return (0);
	}
	if (next->kind != TK_WORD)
	{
		err_msg(next->lexeme);
		return (0);
	}
	return (1);
}

int	syntax_check(t_dlist *tk_lst)
{
	t_node	*node;
	t_token	*token;

	if (!tk_lst || !tk_lst->size)
		return (0);
	node = tk_lst->head;
	while (node)
	{
		if (!node->data)
			return (0);
		token = (t_token *)node->data;
		if (token->kind == TK_PIPE)
		{
			if(!pipe_check(node))
				return (0);	
		}
		else if (token->kind == TK_IN || token->kind == TK_OUT 
			|| token->kind == TK_APPEND || token->kind == TK_HEREDOC)
		{
			if (!redir_check(node))
				return (0);
		}
		node = node->next;
	}
	return (1);
}
