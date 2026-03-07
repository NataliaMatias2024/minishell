/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_act.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:10:09 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 02:14:37 by namatias         ###   ########.fr       */
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
	if (signal == SIGINT) // CTRL + C = SIGINT -> interrompe (intr)
	{
		//As funçoes da readline n conseguem imprimir uma nova linha, apenas atualizar
		//o ponteiro do texto fazendo ele pular, por isso a linha em branco tem q ser feita
		//"manualmente"
		write(STDOUT_FILENO, "\n", 1);
		//Agora sim avisamos ao ponteiro que temos uma nova linha
		rl_on_new_line();
		//limpamos os textos que possam estar salvos, os substituindo por um espaço em branco ""
		//E zeramos o buffer da linha n enviada
		rl_replace_line ("", 0);
		//Agora damos um "F5", informando que fizemos mudanças e queremos um novo prompt
		//com as mudanças implementadas
		rl_redisplay();
	}
}


void	handle_signals_executing(int signal)
{
	g_signal = signal;
	if (signal == SIGQUIT) 	//SIGQUIT (Ctrl-\)
	{
		ft_putendl_fd("minishell: Quit (core dumped)", STDERR_FILENO);
	}
	else if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
}
