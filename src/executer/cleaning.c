/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:41:02 by namatias          #+#    #+#             */
/*   Updated: 2026/03/02 19:49:06 by namatias         ###   ########.fr       */
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

// //TODO: Só dará para testar com o parser pronto!!
// void	clear_child_process(t_exec *exec)
// {
// 	//limpar o historico do readline do processo filho
// 	rl_clear_history();
// 	if (exec)
// 	{
// 		if (exec->env_list)
// 			deleting_list(&(exec->env_list));
// 		if (exec->ast_root) //TODO: Adicionar a arvore ao meu exec para poder chamar a funçao d limpeza
// 			free_ast(exec->ast_root); //TODO: Parser fazendo
// 		close(exec->saved_stdin);
// 		close(exec->saved_stdout);
// 	}
// }
