/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:51:35 by mkitano           #+#    #+#             */
/*   Updated: 2026/03/01 16:51:49 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	*is_redir(int kind)
{
	int	flag;

	flag = 0;
	if (kind == TK_IN || kind == TK_OUT || kind == TK_APPEND
		|| kind == TK_HEREDOC)
		flag = 1;
	return (flag);
}

static t_redir	*create_rd(t_token *redir, t_node *name)
{
	t_redir	*rd_node;
	t_token	*filename;

	if (!name)
		return (NULL);
	filename = (t_token *)name->data;
	rd_node = malloc(sizeof(t_redir));
	if (!rd_node)
		return (NULL);
	rd_node->kind = redir->kind;
	rd_node->file = ft_strdup(filename->lexeme);
	if (!rd_node->file)
	{
		free(rd_node);
		return (NULL);
	}
	rd_node->next = NULL;
	return (rd_node);
}

static void	*add_node_back(t_redir **head, t_redir *to_add)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_redir	*extr_redir(t_node *start, t_node *end)
{
	t_redir	*head;
	t_redir	*new;
	t_node	*cur;

	head = NULL;
	cur = start;
	while (cur)
	{
		if (is_redir(((t_token *)cur->data)->kind))
		{
			new = create_rd((t_token *)cur->data, cur->next);
			if (!new)
			{
				free_rdlst(head); //TODO
				return (NULL);
			}
			add_node_back(&head, new);
			cur = cur->next;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (head);
}

t_redir	*create_rd(t_token *redir, t_node *name)
{
	t_redir	*rd_node;
	t_token	*filename;

	if (!name)
		return (NULL);
	filename = (t_token *)name->data;
	rd_node = malloc(sizeof(t_redir));
	if (!rd_node)
		return (NULL);
	rd_node->kind = redir->kind;
	rd_node->file = ft_strdup(filename->lexeme);
	if (!rd_node->file)
	{
		free(rd_node);
		return (NULL);
	}
	rd_node->next = NULL;
	return (rd_node);
}
