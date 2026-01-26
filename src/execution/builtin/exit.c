/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:00:38 by namatias          #+#    #+#             */
/*   Updated: 2026/01/26 18:07:52 by namatias         ###   ########.fr       */
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

	exit_flag = 0;
	if (args[2])
	{
		if (!ft_is_valid(args[2]))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("exit: numeric argument required.", STDERR_FILENO);
			exit(2);
		}
		else if (args[3])
		{
			ft_putendl_fd("exit: too many arguments.", STDERR_FILENO);
			return (1);
		}
		exit_flag = ft_atoi(args[2]);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_flag);
	return (0);
}
