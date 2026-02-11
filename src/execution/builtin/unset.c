/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:50:36 by namatias          #+#    #+#             */
/*   Updated: 2026/02/11 15:05:54 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_environment	*get_and_detach_node(t_environment **head, char *args);

//Apaga uma variável do ambiente
//retorna sucess a menos q uma opçao invalida seja dada ou seja um NAME read-only
int builtin_unset(t_environment **head, char **args)
{
	int				i;
	t_environment	*target_node;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		target_node = get_and_detach_node(head, args[i]);
		if (!target_node)
			return (0);
		print_list(target_node);
		i++;
		deleting_node(target_node);
	}
	return (0);
}

static t_environment	*get_and_detach_node(t_environment **head, char *args)
{
	t_environment	*temp;
	t_environment	*target_node;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->variable, args) == 0)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	//essa linha será a responsável por destacar esse nó e refazer as ligaçoes da lista para q
	//as outras informaçoes nao sejam perdidas
	target_node = detach_node(head, temp);
	return (target_node);
}
