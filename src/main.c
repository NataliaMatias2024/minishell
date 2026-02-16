/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 22:44:53 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_is_space(char *line);
static void		free_split(char **splited);
char 			**tokens_to_argv(t_dlist *tklst);

/*Integraçao da MAIN para teste*/
int main(int argc, char **argv, char **envp)
{
    t_dlist         *tklst;
    t_environment   *env_list;
    char            *line;
    char            **cmd_args;

	(void)argv;
	(void)argc;
    env_list = init_environment(envp);
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
                // CONVERSÃO (Transforma a lista de tokens em char ** para os built-ins)
                cmd_args = tokens_to_argv(tklst); //TODO

                //EXECUÇÃO DE BUILT-INS
                if (is_builtin_command(&env_list, cmd_args))
                    exec_builtin(env_list, cmd_args);
                else
                    printf("Comando nao encontrado: %s\n", line);

				//LIMPEZA libera as structs
                ft_destroy_dlst(&tklst, free_tks);
                free_split(cmd_args);
            }
			else
				return (1);
        }
        free(line);
    }
    rl_clear_history();
    deleting_list(&env_list);
    printf("Exiting Minishell... (Ctrl + D)\n");
    return (0);
}

char **tokens_to_argv(t_dlist *tklst)
{
    t_node  *node;
    t_token *token;
    char    **args;
    int     i;

    // Conta tokens do tipo WORD para dar o malloc
    args = ft_calloc(tklst->size + 1, sizeof(char *));
    
    node = tklst->head;
    i = 0;
    while (node)
    {
        token = (t_token *)node->data;
        // Só adicionamos ao args o que for palavra (ignora pipes/redirs por enquanto)
        if (token->kind == TK_WORD) 
        {
            args[i] = ft_strdup(token->lexeme);
            i++;
        }
        node = node->next;
    }
    return (args);
}

/*função para teste do tokenize*/
// static char *kind_to_str(t_tk_kind kind)
// {
// 	if (kind == TK_WORD)
// 		return ("WORD");
// 	if (kind == TK_PIPE)
// 		return ("PIPE");
// 	if (kind == TK_IN)
// 		return ("IN");
// 	if (kind == TK_OUT)
// 		return ("OUT");
// 	if (kind == TK_HEREDOC)
// 		return ("HEREDOC");
// 	if (kind == TK_APPEND)
// 		return ("APPEND");
// 	if (kind == TK_EOF)
// 		return ("EOF");
// 	return ("UNKNOWN");
// }
/*main para teste do tokenize*/
/*int	main(int argc, char **argv)
{
	//teste
	t_dlist	*tklst;
	t_node	*node;
	t_token	*token;

	if (argc < 2)
	{
		printf("Use: ./a.out \"command\"\n");
		return (1);
	}
	tklst = tokenize(argv[1], 0);
	if (!tklst)
		return (1);
	node = tklst->head;
	while (node)
	{
		token = (t_token *) node->data;
		printf("Token: %s\n", kind_to_str(token->kind));
		printf("Lexeme: %s\n\n", token->lexeme);
		node = node->next;
	}
	printf("Chegou ao fim\n");
	ft_destroy_dlst(&tklst, free_tks);
	printf("exec frees\n");
	return (0);
}*/

/*
int main(int argc, char **argv)
{
    char *input;
    t_dlist *tokens;

    (void)argc;
    (void)argv;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;

        tokens = tokenize(input, 0);

        // depois vem parse(tokens)
        // depois execute(...)
    }
}
CONCEITO DE MAIN REALOFICIAL
	while (1)
	{
		input = readline();
		tokens = tokenize(input);
		ast = parse(tokens);
		expand(ast);
		execute(ast);
		free_all();
	}*/

	/*TESTES BUILTIN
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
}*/

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
