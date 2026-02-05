/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:41:57 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/05 19:44:16 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handler_pipe(const char *input, int *i)
{
	t_token	*token;

	if (input[*i + 1] == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2);
		(*i)++;
		return (NULL);
	}
	token = new_token(TK_PIPE, ft_strdup("|")); //TODO new_token
	if (!token)
		return (NULL);
	*i += 1;
	return (token);
}

t_token	*handler_redir(const char *input, int *i)
{
	t_token	*token;

	if (input[*i] == '>' && input[*i + 1] == '>')
		token = new_token(TK_APPEND, ft_strdup(">>"));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		token = new_token(TK_HEREDOC, ft_strdup("<<"));
	else if (input[*i] == '>')
		token = new_token(TK_OUT, ft_strdup(">"));
	else if (input[*i] == '<')
		token = new_token(TK_IN, ft_strdup("<"));
	if (!token)
		return (NULL);
	*i += ft_strlen(token->lexeme);
	return (token);
}

t_token	*handler_word(const char *input, int *i)
{
	
}