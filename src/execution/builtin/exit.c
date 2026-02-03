/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:00:38 by namatias          #+#    #+#             */
/*   Updated: 2026/02/03 14:13:37 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EXIT + FLAG NUMERICA + QUALQUER COISA = ERRO POR MUITOS ARGUMENTOS
//EXIT + ARGUMENTO QUE NAO NUMERICO = erro interno porem sai do shell
//exit + numero = saida
//exit = considerado flag = 0, sai sem erros.
int	builtin_exit(char **args)
{
	int	exit_flag;

	//TODO: verifica oq foi recebido
	// int i = 0;
	// while (args[i])
	// {
	// 	printf("Arg[%d] = %s\n", i,args[i]);
	// 	i++;
	// }
	exit_flag = 0;
	if (args[1])
	{
		if (!ft_is_valid(args[1]))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("exit: numeric argument required.", STDERR_FILENO);
			exit(2);
		}
		else if (args[2])
		{
			ft_putendl_fd("exit: too many arguments.", STDERR_FILENO);
			return (1);
		}
		exit_flag = ft_atoi(args[1]);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_flag);
	return (0);
}
