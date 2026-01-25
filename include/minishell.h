/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:15:03 by namatias          #+#    #+#             */
/*   Updated: 2026/01/25 18:02:33 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include "../lib/libftx/include/libft.h"

/**
 * @brief Tipos de nós da AST
 *
 * NK_COMMAND  -> comando simples (ex: ls, echo, cd, etc)
 * NK_PIPE     -> operador |   (conecta stdout -> stdin)
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

typedef struct s_node
{
	t_node_type		kind;
	struct s_node	*left;
	struct s_node	*right;
	char			**arg;
	t_redir			redir_kind;
}					t_node;

void				teste_print(char *string);
int					teste_valida(char *string);

#endif