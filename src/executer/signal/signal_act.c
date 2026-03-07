/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_act.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:10:09 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 03:32:41 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Global variable used to synchronize the status from the child processes.
** It is updated inside the signal handler when an signal is received.
*/
volatile sig_atomic_t	g_signal = 0;

void	handle_signals_interactive(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
}

void	handle_signals_executing(int signal)
{
	g_signal = signal;
	if (signal == SIGQUIT)
	{
		ft_putendl_fd("minishell: Quit (core dumped)", STDERR_FILENO);
	}
	else if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
}
