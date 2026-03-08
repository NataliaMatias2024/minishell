/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 22:04:03 by namatias          #+#    #+#             */
/*   Updated: 2026/03/08 00:12:44 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	init_t_exec(t_exec exec, char **envp)
{
	exec.env_list = init_environment(envp);
	exec.exit_status = 0;
	exec.backup_stdin = dup(STDIN_FILENO);
	exec.backup_stdout = dup(STDOUT_FILENO);
	exec.ast_root = NULL;
	exec.tklst = NULL;
	return (exec);
}
