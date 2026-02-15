/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 04:04:31 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_is_space(char *line);
static void		free_split(char **splited);

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
			add_history(line);
			if (is_builtin_command(&environment_list, argv))
				exec_builtin(environment_list, argv);
			else
			{
				printf("Comando nao encontrado\n");
				printf("%s\n", line);
			}
			free_split(argv);
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
	deleting_list(&environment_list);
	printf("Ctrl + D Acionado\n");
}

//TODO: Feito apenas para conseguir testar os builtins com uma main temporaria, deletar!

static int	ft_is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

static void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}