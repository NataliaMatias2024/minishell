/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:06:07 by namatias          #+#    #+#             */
/*   Updated: 2026/02/19 21:10:27 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(char *lexeme, int *i);
static char	*expand_lexeme(t_env *env, char *lexeme);
static char	*handle_dollar(t_env *env, char *lexeme, int *i, char *analyzed);
static void	clean_quotes(t_token *token);

int	expand_variable(t_env *env, t_dlist **tklst)
{
	t_node			*node;
	t_token			*token;
	char			*expanded_lexeme;

	if (!env || !tklst)
		return (1);
	node = (*tklst)->head;
	while (node)
	{
		token = (t_token *)node->data;
		if (token->kind == TK_WORD)
		{
			if (ft_strchr(token->lexeme, '$'))
			{
				expanded_lexeme = expand_lexeme(env, token->lexeme);
				free(token->lexeme);
				token->lexeme = expanded_lexeme;
			}
			clean_quotes(token);
		}
		node = node->next;
	}
	return (0);
}

static char	*expand_lexeme(t_env *env, char *lexeme)
{
	int		i;
	char	auxiliar[2];
	char	*analyzed;
	int		state;

	i = 0;
	state = 0;
	auxiliar[1] = '\0';
	analyzed = ft_strdup("");
	while (lexeme[i])
	{
		state = quote_state(lexeme[i], state);
		if (lexeme[i] == '$' && state != 1)
			analyzed = handle_dollar(env, lexeme, &i, analyzed);
		else
		{
			auxiliar[0] = lexeme[i];
			analyzed = join_and_free(analyzed, auxiliar);
			i++;
		}
	}
	return (analyzed);
}

static char	*handle_dollar(t_env *env, char *lexeme, int *i, char *analyzed)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (lexeme[*i] == '?')
	{
		// TODO :var_value = ft_itoa(g_exit_status);
		var_value = ft_strdup("0");
		analyzed = join_and_free(analyzed, var_value);
		free(var_value);
		(*i)++;
	}
	else
	{
		var_name = get_name(lexeme, i);
		if (!var_name)
		{
			analyzed = join_and_free(analyzed, "$");
			return (analyzed);
		}
		var_value = get_env_path(&env, var_name);
		free(var_name);
		if (var_value)
			analyzed = join_and_free(analyzed, var_value);
	}
	return (analyzed);
}

static char	*get_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = (*i);
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (NULL);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

static void	clean_quotes(t_token *token)
{
	char	*cleaned_lexeme;

	cleaned_lexeme = remove_quotes(token->lexeme);
	free (token->lexeme);
	token->lexeme = cleaned_lexeme;
}
