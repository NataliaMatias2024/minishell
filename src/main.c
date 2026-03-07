/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:15:20 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 11:16:53 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*função para teste*/
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
/* Teste print com indent (tabs, mas esta espelhado)
static void print_args(char **argv)
{
	int i;

	i = 0;
	while (argv && argv[i])
	{
		printf("%s ", argv[i]);
		i++;
	}
}

static void print_redir(t_redir *redir)
{
	while (redir)
	{
		printf(" %s %s", kind_to_str(redir->kind), redir->file);
		redir = redir->next;
	}
}

static void print_node(t_ast *ast)
{
	if (!ast)
		return ;

	if (ast->type == ND_PIPE)
	{
		printf("PIPE\n");
	}
	else if (ast->type == ND_CMD)
	{
		printf("CMD ");

		print_args(ast->arg);

		if (ast->redir_lst)
			print_redir(ast->redir_lst);

		printf("\n");
	}
}

static void print_ast(t_ast *ast, int depth)
{
	int i;

	if (!ast)
		return ;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}

	print_node(ast);

	if (ast->type == ND_PIPE)
	{
		print_ast(ast->left, depth + 1);
		print_ast(ast->right, depth + 1);
	}
}*/
// Teste print sem tabs
static char	*node_type(t_node_type type)
{
	if (type == ND_PIPE)
		return ("PIPE");
	if (type == ND_CMD)
		return ("CMD");
	return ("ACESSOU NULL?");
}

static void	print_node(t_ast *ast)
{
	t_redir	*redir;
	int		i;

	if (!ast)
		return ;
	if (ast->type == ND_PIPE)
		printf("node: %s\n", node_type(ast->type));
	else
    {
        printf("node: %s ", node_type(ast->type));

        if (ast->arg)
        {
            printf("args: ");
            i = 0;
            while (ast->arg[i])
            {
                printf("%s ", ast->arg[i]);
                i++;
            }
        }
        redir = ast->redir_lst;
        while (redir)
        {
            printf("redir_type: %s ", kind_to_str(redir->kind));
            printf("file: %s ", redir->file);
            redir = redir->next;
        }

        printf("\n");
    }
}

static void	print_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == ND_PIPE)
	{
		print_node(ast);
		print_ast(ast->left);
		print_ast(ast->right);
	}
	else if (ast->type == ND_CMD)
		print_node(ast);
}

/*main para teste do ast*/
int	main(int argc, char **argv)
{
	//teste
	t_dlist	*tklst;
	//t_node	*node;
	//t_token	*token;
	t_ast	*ast_nd;

	if (argc < 2)
	{
		printf("Use: ./a.out \"command\"\n");
		return (1);
	}
	tklst = tokenize(argv[1], 0);
	if (!tklst)
		return (1);
	/*node = tklst->head;
	while (node)
	{
		token = (t_token *) node->data;
		printf("Token: %s\n", kind_to_str(token->kind));
		printf("Lexeme: %s\n\n", token->lexeme);
		node = node->next;
	}*/
	if (!syntax_check(tklst))
	{
		ft_destroy_dlst(&tklst, free_tks);
		printf("syntax achou erro, exec frees\n");
		return(1);
	}
	ast_nd = build_ast(tklst->head, tklst->tail->prev);
	ft_destroy_dlst(&tklst, free_tks);
	printf("tokens frees\n");
	print_ast(ast_nd);
	free_ast(ast_nd);
	printf("ast freed\n");
	return (0);
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
}*/
