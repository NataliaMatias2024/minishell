/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 21:09:37 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;
	char	*line;

	(void)argv;
	(void)argc;
	line = NULL;
	init_shell(&exec, envp);
	exec_readline_looping(line, &exec);
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_clean_all(&exec);
	return (exec.exit_status);
}
