/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:06:52 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 02:14:35 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	//SIGINT (Ctrl-C)
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_signals_interactive; // Aponta para a função q vai lidar com esse sinal;
	sigaction(SIGINT, &sa_int, NULL);

	//SIGQUIT (Ctrl-\)
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;       // Macro da propria biblioteca que ignora o tipo de sinal indicado
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	set_signals_executing(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

 
	//SIGINT (Ctrl-C)
	//Quando estamos no meio de alguma execuçao essa funçao imprime a nova linha MAS
	//n cria novo prompt apenas deixa o processo morrer e continua o looping padrao (com a nova linha)
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_signals_executing;
	sigaction(SIGINT, &sa_int, NULL);

	//SIGQUIT (Ctrl-\)
	//Quando estamos no meio de uma execuçao que trava, o ctrl + \ deve sair d fato e n ser ignorado
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = handle_signals_executing;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	set_signals_default(void)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_int;

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa_quit, NULL);

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_int, NULL);	
}

void	set_signals_ignore(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	//SIGINT (Ctrl-C)
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = SIG_IGN; // Macro da propria biblioteca que ignora o tipo de sinal indicado
	sigaction(SIGINT, &sa_int, NULL);

	//SIGQUIT (Ctrl-\)
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;       // Macro da propria biblioteca que ignora o tipo de sinal indicado
	sigaction(SIGQUIT, &sa_quit, NULL);
}