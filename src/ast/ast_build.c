/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:52:42 by mkitano           #+#    #+#             */
/*   Updated: 2026/03/01 10:44:18 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*find_pipe(t_node *start, t_node *end)
{
	t_node	*curr;

	curr = start;
	while (curr)
	{
		if (((t_token *)curr->data)->kind == TK_PIPE)
			return (curr);
		if (curr == end)
			break ;
		curr = curr->next;
	}
	return (NULL);
}

//depois usa na main de forma recursiva
t_ast	*build_ast(t_node *start, t_node *end)
{
	t_node	*pipe_nd;

	if (!start)
		return (NULL);
	pipe_nd = find_pipe(start, end);
	if (pipe_nd)
		return (create_pipe_nd(pipe_nd, start, end));
	return (create_cmd_nd(start, end));
}
