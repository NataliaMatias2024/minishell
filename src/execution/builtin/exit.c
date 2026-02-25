/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:00:38 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 05:08:32 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EXIT + FLAG NUMERICA + QUALQUER COISA = ERRO POR MUITOS ARGUMENTOS
//EXIT + ARGUMENTO QUE NAO NUMERICO = erro interno porem sai do shell
//exit + numero = saida
//exit = considerado flag = 0, sai sem erros.

static int	ft_is_valid(char *string);

int	builtin_exit(t_env **env, char **args)
{
	int	exit_flag;

	exit_flag = 0;
	if (args[1])
	{
		if (!ft_is_valid(args[1]))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("exit: numeric argument required.", STDERR_FILENO);
			deleting_list(env);
			//retorna 2 para erros relacionados a args nao numericos
			exit(2);
		}
		else if (args[2])
		{
			ft_putendl_fd("exit: too many arguments.", STDERR_FILENO);
			//retorna 1 para erros com muitos args, como nao executa o exit nesses casos o programa n fecha
			//E por isso temos que salvar esse retorna na variavel global
			return (1);
		}
		exit_flag = (ft_atoi(args[1]) % 256);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	deleting_list(env);
	//O status de saída é passado para o shell (processo pai) através de um int.
	// O Linux reserva apenas os 8 primeiros bits para o código de saída digitado no exit
	//Por isso usamos o modulo 256, assim independente doq for digitado fica no range de (0-255).
	//O restante dos bits indica se o processo foi interrompido por sinais 
		//Ex: SIGINT/Ctrl+C ou gerou Core Dump.
	//Assim exit(256) = 0, exit (1000) = 232
	exit(exit_flag % 256);
	return (0);
}

static int	ft_is_valid(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '-' || string[i] == '+')
		i++;
	if (!string[i])
		return (0);
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}
