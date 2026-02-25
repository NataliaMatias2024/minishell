/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/02/25 01:08:26 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Integraçao da MAIN para teste*/
int	main(int argc, char **argv, char **envp)
{
	t_dlist	*tklst;
	t_exec	exec;
	char	*line;
	char	**cmd_args;

	(void)argv;
	(void)argc;
	// Para iniciar sempre usamos ponto (.) em vez de seta (->)
	exec.env_list = init_environment(envp);
	exec.exit_status = 0;
	exec.token = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Trata o Ctrl+D (EOF)
			break ;
		if (*line && ft_is_space(line) != 0)
		{
			add_history(line);
			//TOKEN alimenta a tklst
			tklst = tokenize(line, 0);
			if (tklst)
			{
				//ANTES DA CONVERSAO comandos são expandidos e aspas externas removidas
				expand_variable(&exec, &tklst);

				// CONVERSÃO (Transforma a lista de tokens em char ** para os built-ins)
				cmd_args = tokens_to_argv(tklst);

				//Verifica se tem comandos a serem executados e nao foi apenas um enter
				if (cmd_args && cmd_args[0])
					//Verifica o tipo de comando (externo ou builtin) e executa
					execute_handler(&exec, cmd_args);

				//LIMPEZA libera as structs
				ft_destroy_dlst(&tklst, free_tks);
				free_split(cmd_args);
			}
		}
		free(line);
	}
	rl_clear_history();
	deleting_list(&(exec.env_list));
	printf("Exiting Minishell... (Ctrl + D)\n");
	return (0);
}
