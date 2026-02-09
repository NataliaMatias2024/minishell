/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:44:53 by namatias          #+#    #+#             */
/*   Updated: 2026/02/09 10:50:38 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo basicamente imprime uma string na tela 
//para o subject a unica flag q devemos implementar é echo -n
//echo -n -> nao mostra no output com a quebra de linha no final
//TODO: SE houver aspas duplas hello $USER expande e aparece hello valor de $USER
//TODO: SE houver aspas simples hello $USER aparece exatamente assim
int	builtin_echo(char **args)
{
	int	i;
	if (!args[1])
	{
		printf("\n");
		return (1);
	}
	else if (ft_strcmp(args[1], "-n") == 0)
	{
		i = 2;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}
