/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 13:51:16 by mkitano           #+#    #+#             */
/*   Updated: 2026/03/01 17:30:58 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_arg(t_node *start, t_node *end)
{
	int		count;
	t_node	*cur;
	t_token	*token;

	count = 0;
	cur = start;
	while (cur)
	{
		token = (t_token *)cur->data;
		if (token->kind == TK_IN || token->kind == TK_OUT
			|| token->kind == APPEND || token->kind == TK_HEREDOC)
			cur = cur->next;
		else if (token->kind == TK_WORD)
			count++;
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (count);
}

static char	**lst_to_arg(char **argv, t_node *cur, t_node *end, int i)
{
	t_token	*token;

	while (cur)
	{
		token = (t_token *)cur->data;
		if (token->kind == TK_IN || token->kind == TK_OUT
			|| token->kind == APPEND || token->kind == TK_HEREDOC)
			cur = cur->next;
		else if (token->kind == TK_WORD)
		{
			argv[i] = ft_strdup (token->lexeme);
			if (!argv[i])
			{
				free_argv(argv); //TODO
				return (NULL);
			}
			i++;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

char	**fill_arg(t_node *start, t_node *end)
{
	t_node	*cur;
	char	**argv;
	int		size;

	size = count_arg(start, end);
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	cur = start;
	if (!lst_to_arg(argv, cur, end, 0))
		return (NULL);
	return (argv);
}

static int	*is_redir(int kind)
{
	int	flag;

	flag = 0;
	if (kind == TK_IN || kind == TK_OUT || kind == TK_APPEND
		|| kind == TK_HEREDOC)
		flag = 1;
	return (flag);
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
			add_node_back(&head, new); //TODO
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

//TODO organizar os .c, tem mais de 5 funções por arquivo, dividir entre redir e arg functions