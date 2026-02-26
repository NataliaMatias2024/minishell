/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/02/26 15:21:04 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// MOCKING t_dtlist
t_dlist *test_redirection_manual(void)
{
    t_dlist	*redirs;
	t_redir	*r1;
	t_redir	*r2;
	t_redir	*r3;
	t_redir	*r4;

// 1. Inicializa o controlador da lista (head, tail e size = 0)
	redirs = ft_dlist_initi(); //
	if (!redirs)
		return NULL;

// 2. Cria o primeiro nó de redirecionamento (ls > output.txt)
	r1 = malloc(sizeof(t_redir));
	r1->kind = REDIR_IN;
	r1->filename = ft_strdup("output.txt");
	r2 = malloc(sizeof(t_redir));
	r2->kind = REDIR_OUT;
	r2->filename = ft_strdup("output.txt");
	r3 = malloc(sizeof(t_redir));
	r3->kind = APPEND;
	r3->filename = ft_strdup("output.txt");
	r4 = malloc(sizeof(t_redir));
	r4->kind = HEREDOC;
	r4->filename = ft_strdup("output.txt");

// 3. Adiciona o nó na lista
	ft_lst_push_back(redirs, r1);
	ft_lst_push_back(redirs, r2);
	ft_lst_push_back(redirs, r4);
	ft_lst_push_back(redirs, r3);

	return (redirs);
}


/*Integraçao da MAIN para teste*/
// int	main(int argc, char **argv, char **envp)
// {
// 	t_dlist	*tklst;
// 	t_exec	exec;
// 	char	*line;
// 	char	**cmd_args;
// 	//t_dlist *mock_redirs; // Variável para o teste

// 	(void)argv;
// 	(void)argc;
// 	// Para iniciar sempre usamos ponto (.) em vez de seta (->)
// 	exec.env_list = init_environment(envp);
// 	exec.exit_status = 0;
// 	exec.saved_stdin = dup(STDIN_FILENO);
//     exec.saved_stdout = dup(STDOUT_FILENO);

// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line) // Trata o Ctrl+D (EOF)
// 			break ;
// 		if (*line && ft_is_space(line) != 0)
// 		{
// 			add_history(line);
// 			//TOKEN alimenta a tklst
// 			tklst = tokenize(line, 0);
// 			if (tklst  && syntax_check(tklst))
// 			{
// 				//ANTES DA CONVERSAO comandos são expandidos e aspas externas removidas
// 				expand_variable(&exec, &tklst);

// 				// CONVERSÃO (Transforma a lista de tokens em char ** para os built-ins)
// 				cmd_args = tokens_to_argv(tklst);

// 				//Verifica se tem comandos a serem executados e nao foi apenas um enter
// 				if (cmd_args && cmd_args[0])
// 					//Verifica o tipo de comando (externo ou builtin) e executa
// 					execute_handler(&exec, cmd_args);

// 				//LIMPEZA libera as structs
// 				ft_destroy_dlst(&tklst, free_tks);
// 				free_split(cmd_args);
// 			}
// 			else if (tklst && !syntax_check(tklst))
// 			{
// 				ft_destroy_dlst(&tklst, free_tks);
// 			//	return(1);
// 			}
// 		}
// 		free(line);
// 	}
// 	rl_clear_history();
// 	deleting_list(&(exec.env_list));
// 	printf("Exiting Minishell... (Ctrl + D)\n");
// }

/*MAIN PARA MOCKING*/
int main(int argc, char **argv, char **envp)
{
    t_dlist *tklst;
    t_exec  exec;
    char    *line;
    char    **cmd_args;
    t_dlist *mock_redirs; // Variável para o teste

    (void)argv;
	(void)argc;

    // INICIALIZAÇÃO
    exec.env_list = init_environment(envp);
    exec.exit_status = 0;
    exec.saved_stdin = dup(STDIN_FILENO);
    exec.saved_stdout = dup(STDOUT_FILENO);

    while (1)
    {
        line = readline("minishell> ");
        if (!line) break ;
        if (*line && ft_is_space(line) != 0)
        {
            add_history(line);
            tklst = tokenize(line, 0);
            if (tklst && syntax_check(tklst))
            {
                expand_variable(&exec, &tklst);
                cmd_args = tokens_to_argv(tklst);

                if (cmd_args && cmd_args[0])
                {
                    // --- ÁREA DE TESTE: REDIRECIONAMENTO ---
                    // Simulando que o parser achou um "> teste.txt"
                    mock_redirs = test_redirection_manual();

                    // 1. Aplica o desvio //TODO
                    apply_all_redirections(&exec, mock_redirs);

                    // 2. Executa (O output vai para o arquivo!)
                    execute_handler(&exec, cmd_args);

                    // 3. RESTAURA o terminal para o próximo prompt
                    dup2(exec.saved_stdout, STDOUT_FILENO);

                    // Limpa o mock
                    ft_destroy_dlst(&mock_redirs, free);
                    // ---------------------------------------
                }

                ft_destroy_dlst(&tklst, free_tks);
                free_split(cmd_args);
            }
        }
        free(line);
    }
    // Limpeza final
    close(exec.saved_stdin);
    close(exec.saved_stdout);
    rl_clear_history();
    deleting_list(&(exec.env_list));
    return (0);
}
