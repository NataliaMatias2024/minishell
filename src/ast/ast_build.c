/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:52:42 by mkitano           #+#    #+#             */
/*   Updated: 2026/03/09 20:48:25 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*find_pipe(t_node *start, t_node *end)
{
	t_node	*curr;

	curr = end;
	while (curr)
	{
		if (((t_token *)curr->data)->kind == TK_PIPE)
			return (curr);
		if (curr == start)
			break ;
		curr = curr->prev;
	}
	return (NULL);
}

t_ast	*build_ast(t_node *start, t_node *end)
{
	t_node	*pipe_nd;

	if (!start || !end)
		return (NULL);
	pipe_nd = find_pipe(start, end);
	if (pipe_nd)
		return (create_pipe_nd(pipe_nd, start, end));
	return (create_cmd_nd(start, end));
}
