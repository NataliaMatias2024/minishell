/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/02/02 18:52:36 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_environment	*environment_list;

	environment_list = init_environment(envp);
	if (argc >= 2)
	{
		if (!ft_strcmp(argv[1], "pwd"))
			builtin_pwd();
		else if (!ft_strcmp(argv[1], "exit"))
			builtin_exit(argv);
		else if (!ft_strcmp(argv[1], "cd"))
			builtin_cd(argv);
		else
		{
			printf("Comando nao encontrado\n");
		}
	}
}

