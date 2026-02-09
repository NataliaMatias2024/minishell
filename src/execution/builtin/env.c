/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:59:49 by namatias          #+#    #+#             */
/*   Updated: 2026/02/09 12:46:44 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//mostra a lista com as variaveis de ambiente no formato name=value
//unico se digitar alguma coisa a mais (sem ser as flags) = No such file or directory
//Retorna 125 se o comando em si falhar, 126 se comando foi encontrado mas n pode ser exec
//127 se comando não encontrado
int	builtin_env(t_environment *head, char **args)
{
	if (!head)
		return (1);
	else if (args[0] && args[1])
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (127);
	}
	else
		print_list(head);
	return (0);
}
