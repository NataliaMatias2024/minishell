/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg.c                                          :+:      :+:    :+:   */
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
			|| token->kind == TK_APPEND || token->kind == TK_HEREDOC)
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
			|| token->kind == TK_APPEND || token->kind == TK_HEREDOC)
			cur = cur->next;
		else if (token->kind == TK_WORD)
		{
			argv[i] = ft_strdup (token->lexeme);
			if (!argv[i])
			{
				free_argv(argv);
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
