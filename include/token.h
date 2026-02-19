/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:28:16 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/19 03:11:36 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/*
 * @brief Tipos tokens
 *
 * TK_WORD → palavras normais (ls, echo, oi)
 * TK_PIPE → operador |
 * TK_EOF → fim da lista de tokens (end of file)
 * 
 * t_token_handler → é um ponteiro para função que cria tokens, 
 * “endereço de uma função que retorna t_token *
 */

typedef enum e_tk_kind
{
	TK_WORD,
	TK_PIPE,
	TK_IN,
	TK_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_EOF
}	t_tk_kind;

typedef struct s_token
{
	t_tk_kind	kind;
	char		*lexeme;
}	t_token;

typedef t_token	*(*t_token_handler)(const char *input, int *i);

t_dlist	*tokenize(const char *input, int i);

t_token	*handler_pipe(const char *input, int *i);
t_token	*handler_redir(const char *input, int *i);
t_token	*handler_word(const char *input, int *i);

t_token	*new_token(t_tk_kind kind, char *lexeme);
void	free_tks(void *data);

#endif
