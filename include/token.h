/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:28:16 by mkitano           #+#    #+#             */
/*   Updated: 2026/01/25 18:05:24 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/**
 * @brief Tipos tokens
 *
 * TK_WORD → palavras normais (ls, echo, oi)
 * TK_PIPE → operador |
 * TK_EOF → fim da lista de tokens
 * 
 */

typedef enum e_tk_kind
{
	TK_WORD,
	TK_PIPE,
	TK_EOF  // end of file
}	t_tk_kind;

typedef struct s_token
{
	t_tk_kind	kind;
	char		*lexeme;
}	t_token;

typedef t_token	*(*t_token_handler)(const char *input, int *i);

#endif

