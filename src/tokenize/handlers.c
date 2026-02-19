/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:41:57 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/19 02:25:33 by namatias         ###   ########.fr       */
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
	token = new_token(TK_PIPE, ft_strdup("|"));
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
	else
		token = new_token(TK_IN, ft_strdup("<"));
	if (!token)
		return (NULL);
	*i += ft_strlen(token->lexeme);
	return (token);
}

static int	check_quotes(const char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (0);
	(*i)++;
	return (1);
}

t_token	*handler_word(const char *input, int *i)
{
	t_token	*token;
	int		start;
	char	quote;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_strchr("|<>", input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			if (!check_quotes(input, i, quote))
			{
				ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
				return (NULL);
			}
		}
		else
			(*i)++;
	}
	token = new_token(TK_WORD, ft_substr(input, start, *i - start));
	if (!token)
		return (NULL);
	return (token);
}
