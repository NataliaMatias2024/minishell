/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:15:03 by namatias          #+#    #+#             */
/*   Updated: 2026/03/12 16:23:58 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

// ==========================================
//             STANDARD LIBRARIES
// ==========================================
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

// ==========================================
//           FORWARD DECLARATIONS
// ==========================================
typedef struct s_ast			t_ast;
typedef struct s_environment	t_env;
typedef struct s_node			t_node;
typedef struct s_dlist			t_dlist;
typedef struct s_token			t_token;
typedef struct s_redir			t_redir;

// ==========================================
//             PROJECT HEADERS
// ==========================================
# include "token.h"
# include "ast.h"
# include "execution.h"
# include "../lib/libftx/include/libft.h"

// ==========================================
//             GLOBAL VARIABLE
// ==========================================
/*
** Global variable used to synchronize the status from the child processes.
** It is updated inside the signal handler when a signal is received.
*/
extern volatile sig_atomic_t	g_signal;

#endif
