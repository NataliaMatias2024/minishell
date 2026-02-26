/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:10:35 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/25 13:12:45 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operartor(t_token *token)
{
	t_tk_kind	kind;

	kind = token->kind;
	if (kind == TK_PIPE)
		return (TK_PIPE);
	else if (kind == TK_EOF)
		return (TK_EOF);
	return (-1);
}

int	is_redir(t_token *token)
{
	t_tk_kind	kind;

	kind = token->kind;
	if (kind == TK_IN)
		return (TK_IN);
	else if (kind == TK_OUT)
		return (TK_OUT);
	else if (kind == TK_APPEND)
		return (TK_APPEND);
	else if (kind == TK_HEREDOC)
		return (TK_HEREDOC);
	return (-1);
}
