/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:44:53 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 03:02:22 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo basicamente imprime uma string na tela 
//para o subject a unica flag q devemos implementar é echo -n
//TODO: SE houver aspas duplas hello $USER expande e aparece hello valor de $USER
//TODO: SE houver aspas simples hello $USER aparece exatamente assim

static int	exist_flag(t_env **head, char *str);

int	builtin_echo(t_env **head, char **args)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	if (!args[1]) //apenas echo -> imprime uma nova linha vazia
	{
		printf("\n");
		return (0);
	}
	i = 1;
	//verificamos se existe uma flag -n e salvamos flag_n =1 caso exista
	while (args[i] && exist_flag(head, args[i]))
	{
		flag_n = 1;
		i++;
	}
	//printamos o conteudo na tela acrescentando um espaço entre as palavras
	//exceto na ultima posiçao (args[i + 1] == NULL)
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	//echo -n -> nao mostra no output com a quebra de linha no final
	if (flag_n != 1)
		printf("\n");
	return (0);
}

static int	exist_flag(t_env **head, char *str)
{
	int	i;

	(void)*head;
//se logo de cara não houver -n nao é a flag q queremos, entao apenas retornamos 0 para a func principal
	if (!str || str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
//echo acheita multiplos -n e -nnnnnn... por isso é necessario o looping
//se ja temos o -n verificado, agora vemos se ele é precedido de outros n, pois nesse caso conta como uma unica flag
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
