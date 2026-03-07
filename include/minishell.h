/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:15:03 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 02:52:10 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

//Bibliotecas Padrão do C
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

//Bibliotecas do Sistema (POSIX)
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//Bibliotecas Externas (Readline)
# include <readline/history.h>
# include <readline/readline.h>

// Bibliotecas Customizadas (libftx)
# include "../lib/libftx/include/libft.h"

// Variavél Global para lidar com os sinais
extern volatile sig_atomic_t g_signal;

/**
 * @brief Organização Modular dos Headers
 *
 * EXECUTION.H -> Hub principal da execução, consolidando:
 * - ENVIRONMENT.H: Definição da t_environment e gestão de memória da env.
 * - BUILTIN.H:     Protótipos dos comandos internos (echo, cd, pwd, etc).
 * - EXPANSION.H:   Lógica de expansão de variáveis ($) e tratamento de aspas.
 *
 */
# include "execution.h"



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
# include "token.h"
# include "ast.h"

typedef struct s_redir	t_redir;

typedef struct s_nodem
{
	t_node_type		kind;
	struct s_node	*left;
	struct s_node	*right;
	char			**arg;
	t_redir			redir_kind;
}					t_nodem;

//para teste main
int		syntax_check(t_dlist *tk_lst);
int		pipe_check(t_node *node);
int		redir_check(t_node *node);
void	err_msg(char *lex);

#endif
