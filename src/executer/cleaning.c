/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:41:02 by namatias          #+#    #+#             */
/*   Updated: 2026/03/08 14:47:54 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	deleteting_all_nodes(t_env **head);

void	deleting_node(t_env *to_delete)
{
	if (!to_delete)
		return ;
	if (to_delete->value)
	{
		free(to_delete->value);
		to_delete->value = NULL;
	}
	if (to_delete->variable)
	{
		free(to_delete->variable);
		to_delete->variable = NULL;
	}
	free(to_delete);
}

static void	deleteting_all_nodes(t_env **head)
{
	t_env	*current_node;
	t_env	*temp;

	if (!head || !*head)
		return ;
	current_node = (*head);
	while (current_node)
	{
		temp = current_node->next;
		deleting_node(current_node);
		current_node = temp;
	}
}

void	deleting_list(t_env **head)
{
	if (!head || !*head)
		return ;
	deleteting_all_nodes(head);
	*head = NULL;
}

void	clear_child_process(t_exec *exec)
{
	if (exec)
	{
		if (exec->env_list)
			deleting_list(&(exec->env_list));
		if (exec->ast_root)
			free_ast(exec->ast_root);
		close(exec->backup_stdin);
		close(exec->backup_stdout);
		rl_clear_history();
	}
}

void	free_clean_all(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->env_list)
		deleting_list(&(exec->env_list));
	if (exec->backup_stdin >= 0)
		close(exec->backup_stdin);
	if (exec->backup_stdout >= 0)
		close(exec->backup_stdout);
	if (exec->ast_root)
	{
		free_ast(exec->ast_root);
		exec->ast_root = NULL;
	}
	if (exec->tklst)
	{
		ft_destroy_dlst(&exec->tklst, free_tks);
		exec->tklst = NULL;
	}
	rl_clear_history();
}
