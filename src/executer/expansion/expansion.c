/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:06:07 by namatias          #+#    #+#             */
/*   Updated: 2026/03/02 19:49:17 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_quotes(t_token *token);
static char	*expand_lexeme(t_exec *exec, char *lexeme);

//TODO: Ajustar para quando parser ficar pronto. Temos que verificar SE o token 
int	expand_variable(t_exec *exec, t_dlist **tklst)
{
	t_node			*node;
	t_token			*token;
	char			*expanded_lexeme;

	if (!exec->env_list || !tklst)
		return (1);
	node = (*tklst)->head;
	while (node)
	{
		token = (t_token *)node->data;
		if (token->kind == TK_WORD)
		{
	//Para a funçao funcionar para o heredoc temos que acrescentar uma condiçao para verificar 2 coisas alem da existencia de $
	//1 - Verificar se existe algum node antes doq queremos expandir
	//2 - SE existe verificar se é o nodo do Heredoc ou outro qualquer
	//Isso pq se existir um heredoc anteriormente, esse node se refere ao delimitador e n deve ser expandido
	//MAS deve ter suas aspas retiradas.
			if (!(node->prev &&
				((t_token *)node->prev->data)->kind == TK_HEREDOC) &&
				 ft_strchr(token->lexeme, '$'))
			{
				expanded_lexeme = expand_lexeme(exec, token->lexeme);
				free(token->lexeme);
				token->lexeme = expanded_lexeme;
			}
			clean_quotes(token);
		}
		node = node->next;
	}
	return (0);
}

static char	*expand_lexeme(t_exec *exec, char *lexeme)
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
			analyzed = handle_dollar(exec, lexeme, &i, analyzed);
		else
		{
			auxiliar[0] = lexeme[i];
			analyzed = join_and_free(analyzed, auxiliar);
			i++;
		}
	}
	return (analyzed);
}

char	*handle_dollar(t_exec *exec, char *lexeme, int *i, char *analyzed)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (lexeme[*i] == '?')
	{
		//Transforma o exit_status em string
		var_value = ft_itoa(exec->exit_status);
		//Concatena o valor de $? com o resto da frase ja existente
		analyzed = join_and_free(analyzed, var_value);
		//como ft_itoa faz malloc interno temos que liberar depois de concatenar
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
		var_value = get_env_path(&exec->env_list, var_name);
		free(var_name);
		if (var_value)
			analyzed = join_and_free(analyzed, var_value);
	}
	return (analyzed);
}

char	*get_name(char *str, int *i)
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
