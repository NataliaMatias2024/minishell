/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:15:03 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 21:38:32 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

# include "../lib/libftx/include/libft.h"

/**
 * @brief Organização Modular dos Headers
 *
 * ENVIRONMENT.H -> Definição da struct t_environment e gestão de memória.
 * BUILTIN.H     -> Protótipos dos comandos internos (depende do environment).
 *
 * NOTA: O minishell.h concentra esses includes para servir como hub global.
 */
# include "environment.h"
# include "builtin.h"

# include "token.h"

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

#endif
