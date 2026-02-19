/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:06:07 by namatias          #+#    #+#             */
/*   Updated: 2026/02/19 03:32:57 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(char *lexeme, int *i);
static char	*expand_lexeme(t_env *env, char *lexeme);
static char	*handle_dollar(t_env *env, char *lexeme, int *i, char *lex_analyzed);

int	expand_variable(t_env *env, t_dlist **tklst)
{
	t_node			*node;
	t_token			*token;
	char			*expanded_lexeme;
	char			*cleaned_lexeme;

	if (!env || !tklst)
		return (1);
	node = (*tklst)->head;
	//garante que todos os nodes serao verificados antes de começar o parser e/ou execuçao
	while (node)
	{
		token = (t_token *)node->data;
		//nodes de pipes/redirect/etc, serao ignorados, apenas os tk_word a ser expandidos serão analisados
		if (token->kind == TK_WORD)
		{
			//apenas os lexemas com $ sofrem expansão o resto pode ser ignorado mesmo tendo aspas
			if (ft_strchr(token->lexeme, '$'))
			{
				expanded_lexeme = expand_lexeme(env, token->lexeme);
				//limpa oq tinha antes nesse node
				free(token->lexeme);
				//atualizamos para o valor com as variáveis expandidas
				token->lexeme = expanded_lexeme;
			}
			//após expandir limpamos as aspas e atualizamos os valores
			cleaned_lexeme = remove_quotes(token->lexeme);
			free (token->lexeme);
			token->lexeme = cleaned_lexeme;
		}
		node = node->next;
	}
	return (0);
}

/*	ENQUANTO lexeme existir
	Verificar se ela esta fora de aspas simples -> UNICO caso q n expande
	SE existir um $ E NAO estiver dentro de aspas simples
		lidar com o sinal de dollar -> handle_$(env, lexeme, &ocorrencia_$, lexeme_analisado);
	SE nao estiver chama
		retorna sem expandir, vira nome literal
		lexeme_analisado = ft_strjoin(lexeme_analisado, lexeme[i]);
OBS: passar &i permite que a posiçao do lexeme seja incrementada ou decrementa por outras funçoes
OBS2: strjoin só funciona com strings, entao nao consiguimos usar com um char direto (fazer maracutaia)*/
static char	*expand_lexeme(t_env *env, char *lexeme)
{
	int		i;
	char	auxiliar[2];
	char	*lex_analyzed;
	int		state;

	i = 0;
	state = 0;
	auxiliar[1] = '\0';
	lex_analyzed = ft_strdup("");
	while (lexeme[i])
	{
		state = quote_state(lexeme[i], state);
		if (lexeme[i] == '$' && state != 1)
			lex_analyzed = handle_dollar(env, lexeme, &i, lex_analyzed);
		else
		{
			auxiliar[0] = lexeme[i];
			lex_analyzed = join_and_free(lex_analyzed, auxiliar);
			i++; //pq aqui e n fora do if e elses? PQ DENTRO DO IF o i avança dentro das outras funçoes.
		}
	}
	return (lex_analyzed);
}

/*Ver a posiçao seguinte do $
		SE $? 
			retorna o ultimo exit_status -> variavel global q coleta tds os retornos e sinais
		SE NAO 
			Le ate encontrar um caracter nao alfa numerico (garantindo q pegou td o nome e q é um nome valido)
			SE var_name retornado for nulo
				imprime o $ + o nome da variavel como string literal -> NAO EXPANDE pois n existe
			SE N
				Compara nome encontrado com os existentes em env e retorna o conteudo da variavel -> get_env_value(env, var_name);
		libera o nome encontrado, evitando leaks
		salvar o valor encontrado no retorno
		    Se achou na env, junta o valor. Se não achou, NÃO FAZ NADA (expande para vazio)
	return (lexeme_analisado);*/
static char	*handle_dollar(t_env *env, char *lexeme, int *i, char *lex_analyzed)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (lexeme[*i] == '?')
	{
		// TODO :var_value = ft_itoa(g_exit_status);
		var_value = ft_strdup("0");
		lex_analyzed = join_and_free(lex_analyzed, var_value);
		free(var_value);
		(*i)++;
	}
	else
	{
		var_name = get_name(lexeme, i);
		if (!var_name)
		{
			lex_analyzed = join_and_free(lex_analyzed, "$");
			return (lex_analyzed);
		}
		var_value = get_env_path(&env, var_name);
		free(var_name);
		if (var_value)
			lex_analyzed = join_and_free(lex_analyzed, var_value);
	}
	return (lex_analyzed);
}

//Analisamos a primeira "letra" da string recebida se nao for alfanumerico nem _ não é variavel valida
//Retorna null, assim a funçao lexama_expanded sabe q precisa colocar string literal e n o valor d uma variavel
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
