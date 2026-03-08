/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/03/08 16:51:39 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_dlist	*tklst;
	t_exec	exec;
	t_ast	*root;
	t_node	*end_node;
	char	*line;

	(void)argv;
	(void)argc;

	exec.env_list = init_environment(envp);
	exec.exit_status = 0;
	exec.backup_stdin = dup(STDIN_FILENO);
	exec.backup_stdout = dup(STDOUT_FILENO);
	exec.ast_root = NULL;
	exec.tklst = NULL;
	set_signals_interactive();

	while (1)
	{
		line = readline("minishell> ");
		if (g_signal == SIGINT) //Verifica se ocorreu ctrl+c
		{
			exec.exit_status = 130; // Atualiza o status
			g_signal = 0;            // Reseta a variável global para o próximo loop não bugar
		}
		if (!line) // Trata o Ctrl+D (EOF)
			break ;
		if (*line && ft_is_space(line) != 0)
		{
			add_history(line);
			tklst = tokenize(line, 0);
			exec.tklst = tklst;

			if (tklst && syntax_check(tklst))
			{
				//expand para executar resto dos comandos
				expand_variable(&exec, &tklst);
				//encontra ultimo nó
				end_node = tklst->head;
				while (end_node && end_node->next)
					end_node = end_node->next;

				//Inicia arvore
				root = build_ast(tklst->head, end_node);
				//dar freee lista
				if (root)
				{
					exec.ast_root = root; // Guarda na struct caso um built-in dê exit e precise dar free_clean_all
					//verifica primeiro heredoc, SE n houver erro executa o resto
					if (scan_ast_heredocs(&exec, root) == 0)
					{
						//Exec com recursao da arvore
						exec_ast(&exec, root, 0);
					}
					//Limpa arvore após executar tds os comandos
					free_ast(root);
					exec.ast_root = NULL;
				}
			}
			//Limpa tokens
			if (tklst)
			{
				ft_destroy_dlst(&tklst, free_tks);
				exec.tklst = NULL;
			}
		}
		free(line);
	}
	//Lipeza Final (Quando sai pelo Ctrl+D)
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_clean_all(&exec);

	return (exec.exit_status);
}
