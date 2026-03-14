/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:14:49 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 21:58:16 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_exec *exec, char **envp)
{
	exec->env_list = init_environment(envp);
	exec->exit_status = 0;
	exec->backup_stdin = dup(STDIN_FILENO);
	exec->backup_stdout = dup(STDOUT_FILENO);
	exec->ast_root = NULL;
	exec->tklst = NULL;
}

void	exec_readline_looping(char *line, t_exec *exec)
{
	t_dlist	*tklst;

	while (1)
	{
		set_signals_interactive();
		line = readline("minishell> ");
		if (g_signal == SIGINT)
		{
			exec->exit_status = 130;
			g_signal = 0;
		}
		if (!line)
			break ;
		if (*line && ft_is_space(line) != 0)
		{
			add_history(line);
			tklst = tokenize(line, 0);
			exec->tklst = tklst;
			if (tklst && syntax_check(tklst))
				exec_ast_logic(exec, tklst);
			clean_tklst(tklst, exec);
		}
		free(line);
	}
}

void	exec_ast_logic(t_exec *exec, t_dlist *tklst)
{
	t_ast	*root;
	t_node	*end_node;

	expand_variable(exec, &tklst);
	end_node = tklst->head;
	while (end_node && end_node->next)
		end_node = end_node->next;
	root = build_ast(tklst->head, end_node);
	if (root)
	{
		exec->ast_root = root;
		if (scan_ast_heredocs(exec, root) == 0)
			exec_ast(exec, root, 0);
		unlink(".heredoc_tmp");
		free_ast(root);
		exec->ast_root = NULL;
	}
}

void	clean_tklst(t_dlist *tklst, t_exec *exec)
{
	if (tklst)
	{
		ft_destroy_dlst(&tklst, free_tks);
		exec->tklst = NULL;
	}
}
