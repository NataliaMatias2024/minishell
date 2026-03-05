/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 21:51:41 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* main.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/* Updated: 2026/03/04 22:15:00 by namatias         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Certifique-se de que a declaração da função da sua dupla está no seu .h
// t_ast *build_ast(t_node *start, t_node *end);
// void  free_ast(t_ast *ast);

int main(int argc, char **argv, char **envp)
{
	t_dlist	*tklst;
	t_exec	exec;
	t_ast	*root;
	t_node	*end_node;
	char	*line;

	(void)argv;
	(void)argc;

	// 1. INICIALIZAÇÃO DA STRUCT PRINCIPAL
	exec.env_list = init_environment(envp);
	exec.exit_status = 0;
	exec.backup_stdin = dup(STDIN_FILENO);
	exec.backup_stdout = dup(STDOUT_FILENO);
	exec.ast_root = NULL; // Importante iniciar como NULL

	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Trata o Ctrl+D (EOF)
			break ;

		if (*line && ft_is_space(line) != 0)
		{
			add_history(line);
			tklst = tokenize(line, 0);
			
			if (tklst && syntax_check(tklst))
			{
				// 2. ENCONTRAR O ÚLTIMO NÓ PARA PASSAR PRO PARSER
				end_node = tklst->head;
				while (end_node && end_node->next)
					end_node = end_node->next;

				// 3. CONSTRUIR A ÁRVORE
				root = build_ast(tklst->head, end_node);

				if (root)
				{
					exec.ast_root = root; // Guarda na struct caso um built-in dê exit e precise dar free_clean_all
					
					// 4. Exec com recursao da arvore
					exec_ast(&exec, root, 0);

					// 5. LIMPEZA DA ÁRVORE APÓS EXECUÇÃO
					// free_ast(root); //TODO: Em andamento
					exec.ast_root = NULL;
				}
			}
			// 6. LIMPEZA DOS TOKENS
			if (tklst)
				ft_destroy_dlst(&tklst, free_tks);
		}
		free(line);
	}
	// 7. LIMPEZA FINAL (Quando sai pelo Ctrl+D)
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_clean_all(&exec);
	
	return (exec.exit_status);
}

// t_redir_type get_redir_type(t_tk_kind kind);
// t_dlist *extract_redirections(t_dlist *tklst);
// char **get_clean_args(t_dlist *tklst);
// void	free_redir_content(void *data);
// char **filter_args_for_exec(t_dlist *tklst);

// /*Integraçao da MAIN para teste*/
// int	main(int argc, char **argv, char **envp)
// {
// 	t_dlist	*tklst;
// 	t_exec	exec;
// 	char	*line;
// 	char	**cmd_args;
// 	t_dlist *mock_redirs; // Variável para o teste

// 	(void)argv;
// 	(void)argc;
// 	// Para iniciar sempre usamos ponto (.) em vez de seta (->)
// 	exec.env_list = init_environment(envp);
// 	exec.exit_status = 0;
// 	exec.backup_stdin = dup(STDIN_FILENO);
//     exec.backup_stdout = dup(STDOUT_FILENO);

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
// 					execute_commands_handler(&exec, cmd_args);

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
//     // Limpeza final
//     close(exec.backup_stdin);
//     close(exec.backup_stdout);
// 	rl_clear_history();
// 	deleting_list(&(exec.env_list));
// 	printf("Exiting Minishell... (Ctrl + D)\n");
// }

// /*MAIN PARA MOCKING*/
// int main(int argc, char **argv, char **envp)
// {
//     t_dlist *tklst;
//     t_exec  exec;
//     char    *line;
//     char    **cmd_args;

//     (void)argv;
// 	(void)argc;

//     // INICIALIZAÇÃO
//     exec.env_list = init_environment(envp);
//     exec.exit_status = 0;
//     exec.backup_stdin = dup(STDIN_FILENO);
//     exec.backup_stdout = dup(STDOUT_FILENO);

//     while (1)
//     {
//         line = readline("minishell> ");
//         if (!line) break ;
//         if (*line && ft_is_space(line) != 0)
//         {
//             add_history(line);
//             tklst = tokenize(line, 0);
//             if (tklst && syntax_check(tklst))
//             {
//                 // 1. EXTRAI redirecionamentos reais dos tokens digitados
//                 t_dlist *real_redirs = extract_redirections(tklst);
//                 // 2. APLICA lógica de redirect
//                 apply_all_redirections(&exec, real_redirs);
//                 //3. EXECUTA o resto dos comando apenas SE os redirect n deram ruim, SE NAO paramos td por aqui!!!
//                 if (exec.exit_status == 0)
//                 {
//                     //4. EXPANDE e FILTRA os argumentos, assim imitamos o comportamento do parser
//                     expand_variable(&exec, &tklst);
//                     cmd_args = filter_args_for_exec(tklst);
//                     if (cmd_args && cmd_args[0])
//                     {
//                         // 5. EXECUTA
//                         execute_commands_handler(&exec, cmd_args); // Por enquanto use cmd_args, mas o ideal será o clean_args
//                     }
//                     // 6. LIMPA o cmd criado para testar execs
//                     if (cmd_args)
//                         free_split(cmd_args);
//                 }
//                 //7. Caso redirect de erro e nada seja executado continuamos precisando LIMPAR e RESTAURAR os FDS
//                 dup2(exec.backup_stdout, STDOUT_FILENO);
//                 dup2(exec.backup_stdin, STDIN_FILENO);
//                 ft_destroy_dlst(&real_redirs, free_redir_content);
//             }
//             //8. Caso tenha dado erro de syntax e token LIMPA apenas a lista de tokens
//             ft_destroy_dlst(&tklst, free_tks);
//         }
//         //9. Libera a linha digitada e reinicia o looping para testar e executar as proximas linhas
//         free(line);
//     }
//     // Limpeza final
//     close(exec.backup_stdin);
//     close(exec.backup_stdout);
//     rl_clear_history();
//     deleting_list(&(exec.env_list));
//     return (0);
// }

// char **get_clean_args(t_dlist *tklst)
// {
//     int     count;
//     char    **args;
//     t_node  *curr;
//     t_token *tok;

//     // Primeiro conta quantos tokens NÃO são redirecionamentos
//     count = 0;
//     curr = tklst->head;
//     while (curr)
//     {
//         tok = (t_token *)curr->data;
//         if (tok->kind == TK_WORD) // Apenas palavras contam como argumentos
//             count++;
//         else
//             curr = curr->next; // Se for redirecionador, pula ele e o arquivo
//         curr = curr->next;
//     }

//     // Aloca o array final
//     args = malloc(sizeof(char *) * (count + 1));
//     // ... lógica de preenchimento similar ao seu tokens_to_argv original ...
//     // mas pulando os tokens onde (kind != TOKEN_WORD)
//     return (args);
// }

// // Função para converter o tipo de Token para o seu tipo de Redir
// t_redir_type get_redir_type(t_tk_kind kind)
// {
//     if (kind == TK_IN) return REDIR_IN;
//     if (kind == TK_OUT) return REDIR_OUT;
//     if (kind == TK_APPEND) return APPEND;
//     return HEREDOC;
// }

// t_dlist *extract_redirections(t_dlist *tklst)
// {
//     t_dlist *redirs;
//     t_node  *curr;
//     t_token *tok;
//     t_redir *r;

//     if (!tklst || !tklst->head) return (NULL);
//     redirs = ft_dlist_initi();
//     curr = tklst->head;
//     while (curr)
//     {
//         tok = (t_token *)curr->data;
//         if (tok->kind == TK_IN || tok->kind == TK_OUT || 
//             tok->kind == TK_APPEND || tok->kind == TK_HEREDOC)
//         {
//             r = malloc(sizeof(t_redir));
//             r->kind = get_redir_type(tok->kind);
//             r->filename = NULL;
            
//             if (curr->next)
//             {
//                 curr = curr->next; // Pula o operador (ex: '>')
//                 if (curr && curr->data) // SÓ acessa se o arquivo existir
//                 {
//                     r->filename = ft_strdup(((t_token *)curr->data)->lexeme);
//                 }
//                 ft_lst_push_back(redirs, r);
//             }
//         }
//         if (curr) // Proteção extra para o final da lista
//             curr = curr->next;
//     }
//     return (redirs);
// }

// void	free_redir_content(void *data)
// {
// 	t_redir	*redir;

// 	redir = (t_redir *)data;
// 	if (!redir)
// 		return ;
// 	if (redir->filename)
// 		free(redir->filename);
// 	free(redir);
// }

// char **filter_args_for_exec(t_dlist *tklst)
// {
//     int     count = 0;
//     t_node  *curr = tklst->head;
//     t_token *tok;
//     char    **args;
//     int     i = 0;

//     // 1. Contagem protegida
//     while (curr)
//     {
//         tok = (t_token *)curr->data;
//         if (tok->kind == TK_WORD)
//             count++;
//         else
//         {
//             curr = curr->next; // Pula o arquivo do redirecionamento
//         }
//         if (curr) curr = curr->next;
//     }

//     args = malloc(sizeof(char *) * (count + 1));
//     if (!args) return (NULL);

//     // 2. Preenchimento protegido
//     curr = tklst->head;
//     while (curr && i < count)
//     {
//         tok = (t_token *)curr->data;
//         if (tok->kind == TK_WORD)
//             args[i++] = ft_strdup(tok->lexeme);
//         else
//         {
//             curr = curr->next; // Pula o nome do arquivo
//         }
//         if (curr) curr = curr->next;
//     }
//     args[i] = NULL;
//     return (args);
// }
