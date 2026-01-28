/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:26:02 by mkitano           #+#    #+#             */
/*   Updated: 2026/01/25 18:37:31 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static int	add_token(t_dlist *tks, t_token *token)
{
	if (!token)
	{
		ft_destroy_dlst(&tks, free_tks);
		return (1);
	}
	if (!ft_push_node_back(tks, token))
	{
		free_tks(token); //TODO
		ft_destroy_dlst(&tks, free_tks);
		return (1);
	}
	return (0);
}

static void	init_disp_table(t_token_handler table[])
{
	ft_bzero(table, sizeof(t_token_handler) * 256);
	table['|'] = &handler_pipe; //TODO
	table['>'] = &handler_redir; //TODO
	table['<'] = &handler_redir;
}

t_dlist	*tokenize(const char *input, int i)
{
	t_token_handler	table[256];
	t_dlist			*tokens;
	t_token			*token;

	init_disp_table(table);
	tokens = ft_dlist_initi();
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		if (table[(int) input[i]] != NULL)
			token = table[(int) input[i]](input, &i);
		else
			token = &handler_word(input, &i); //TODO
		if (add_token(tokens, token))
			return (NULL);
	}
	if (add_token(tokens, new_token(TK_EOF, ft_strdup(""))))
		return (NULL);
	return (tokens);
}
