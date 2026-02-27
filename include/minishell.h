/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:15:03 by namatias          #+#    #+#             */
/*   Updated: 2026/02/01 19:53:54 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

# include "../lib/libftx/include/libft.h"

# include "token.h"
# include "ast.h"

/**
 * @brief Tipos de nós da AST
 *
 * COMMAND  -> comando simples (ex: ls, echo, cd, etc)
 * PIPE     -> operador |   (conecta stdout -> stdin)
 * 
 * REDIR_IN		<
 * REDIR_OUT	>
 * HEREDOC		<<
 * APPEND		>>
 */

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	kind;
	int				fd;
	char			*filename;
}	t_redir;

typedef enum e_node_type
{
	NT_WORD,
	NT_PIPE
}	t_node_type;

typedef struct s_nodem
{
	t_node_type		kind;
	struct s_node	*left;
	struct s_node	*right;
	char			**arg;
	//t_dlist		*args;
	t_redir			redir_kind;
}					t_nodem;

void				teste_print(char *string);
int					teste_valida(char *string);

//para teste main
int	syntax_check(t_dlist *tk_lst);
int pipe_check(t_node *node);
int redir_check(t_node *node);
void err_msg(char *lex);

#endif