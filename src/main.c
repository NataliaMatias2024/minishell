/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/01/21 17:43:42 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*função para teste do tokenize*/
static char *kind_to_str(t_tk_kind kind)
{
	if (kind == TK_WORD)
		return ("WORD");
	if (kind == TK_PIPE)
		return ("PIPE");
	if (kind == TK_IN)
		return ("IN");
	if (kind == TK_OUT)
		return ("OUT");
	if (kind == TK_HEREDOC)
		return ("HEREDOC");
	if (kind == TK_APPEND)
		return ("APPEND");
	if (kind == TK_EOF)
		return ("EOF");
	return ("UNKNOWN");
}
/*main para teste do tokenize*/
int	main(int argc, char **argv)
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
//	if (argc > 1 && teste_valida(argv[1]))
//		teste_print(argv[1]);
}

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