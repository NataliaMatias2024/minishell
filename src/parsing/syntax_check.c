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

#include "minishell"

int pipe_check(t_node *node)
{
	t_token	*token;

	if (!node || !node->data)
		return (0);
	token = (t_token *)node->data;
	if (!node->prev || !node->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|`", 2);
		return (0);
	}
	else if (((t_token *)node->prev->data)->kind == TK_PIPE
		|| ((t_token *)node->next->data)->kind != TK_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|`", 2); //TODO checar mensagem de erro
		return (0);
	}
	return (1);
}

int redir_check(t_node *node)
{
	if (!node || !node->next || ((t_token *)node->next->data)->kind == TK_EOF)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline`", 2);
		return (0);
	}
	else if (((t_token *)node->next->data)->kind != TK_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2); //TODO checar mensagem de erro
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
