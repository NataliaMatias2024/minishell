/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:15:03 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 22:11:47 by namatias         ###   ########.fr       */
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
//             PROJECT HEADERS
// ==========================================
# include "ast.h"
# include "token.h"
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

// ==========================================
//               STRUCTURES
// ==========================================
typedef struct s_redir			t_redir;

typedef struct s_nodem
{
	t_node_type		kind;
	struct s_node	*left;
	struct s_node	*right;
	char			**arg;
	t_redir			redir_kind;
}					t_nodem;

// ==========================================
//               PROTOTYPES
// ==========================================
int		syntax_check(t_dlist *tk_lst);
int		pipe_check(t_node *node);
int		redir_check(t_node *node);
void	err_msg(char *lex);

#endif
