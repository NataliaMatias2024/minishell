/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:58:02 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 15:19:35 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ast(t_exec *exec, t_ast *root, int in_pipe)
{
	if (!root)
		return ;
	if (root->type == ND_PIPE)
		exec_pipe(exec, root);
	else if (root->type == ND_CMD)
		execute_commands_handler(exec, root, 0);
}
