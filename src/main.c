/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/02/07 20:42:21 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char *line);

int	main(int argc, char **argv, char **envp)
{
	t_environment	*environment_list;
	char			*line;

	(void)argc;
	environment_list = init_environment(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (line && *line && ft_is_space(line) != 0)
		{
			argv = ft_split(line, 32);
			//TODO: printf("line = %s\n", line);
			add_history(line);
			if (ft_strcmp(argv[0], "pwd") == 0)
				builtin_pwd(argv);
			else if (ft_strcmp(argv[0], "exit") == 0)
				builtin_exit(argv);
			else if (ft_strcmp(argv[0], "cd") == 0)
				builtin_cd(environment_list, argv);
			else if (ft_strcmp(argv[0], "echo") == 0)
				builtin_echo(argv);
			else
			{
				printf("Comando nao encontrado\n");
				printf("%s\n", line);
			}
		}
		if (line)
		{
			free(line);
			line = (char *) NULL;
		}
		else if (!line)
			break ;
	}
	rl_clear_history();
	printf("Ctrl + D Acionado\n");
}

