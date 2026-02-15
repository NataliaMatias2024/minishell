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

t_token	*new_token(t_tk_kind kind, char *lexeme)
{
	t_token	*token;

	if (!lexeme)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		free(lexeme);
		return (NULL);
	}
	token->kind = kind;
	token->lexeme = lexeme;
	return (token);
}

void	free_tks(void *data)
{
	t_token	*token;

	if (!data)
		return ;
	token = (t_token *) data;
	if (token->lexeme)
		free(token->lexeme);
	free (token);
}
