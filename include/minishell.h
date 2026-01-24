/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:15:03 by namatias          #+#    #+#             */
/*   Updated: 2026/01/21 17:42:35 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>

/**
 * @brief Tipos de nós da AST
 *
 * NK_COMMAND  -> comando simples (ex: ls, echo, cd, etc)
 * NK_PIPE     -> operador |   (conecta stdout -> stdin)
 * NK_LIST     -> operador ;   (executa comandos em sequência)
 * NK_AND      -> operador &&  (executa o próximo se o anterior teve sucesso)
 * NK_OR       -> operador ||  (executa o próximo se o anterior falhar)
 * NK_SUBSHELL -> comandos entre parênteses
 */

typedef enum e_redir_type
{
	REDIR_IN,      // <
	REDIR_OUT,     // >
	HEREDOC,       // <<
	APPEND         // >>
} t_redir_type;

typedef struct s_redir
{
	t_redir_type	kind;
	int				fd;
	char			*filename;
} t_redir;

typedef enum e_node_type
{
	NT_CMD,        // (WORD) ex: ls, grep, txt
	NT_WORD        // "oi mundo"
	NT_PIPE        // |
} t_node_type;

typedef struct s_node
{
	t_node_type		kind;
	struct s_node	*left;
	struct s_node	*right;
	char			**arg;
	t_redir			redir_kind;
} t_node;

void	teste_print(char *string);
int		teste_valida(char *string);

#endif