/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:09:33 by namatias          #+#    #+#             */
/*   Updated: 2026/02/19 03:36:22 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: Verificar oq esta sendo realmente usado e deletar oq n precisar!
int	ft_is_space(char *line)
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

void	free_split(char **splited)
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

char	*get_env_path(t_env **env, char *name)
{
	t_env	*temp_env;

	if (!env)
		return (NULL);
	temp_env = *env;
	while (temp_env)
	{
		if (ft_strcmp(temp_env->variable, name) == 0)
			return (temp_env->value);
		temp_env = temp_env->next;
	}
	return (NULL);
}

char	**tokens_to_argv(t_dlist *tklst)
{
	t_node	*node;
	t_token	*token;
	char	**args;
	int		i;

	args = ft_calloc(tklst->size + 1, sizeof(char *));
	node = tklst->head;
	i = 0;
	while (node)
	{
		token = (t_token *)node->data;
		if (token->kind == TK_WORD)
		{
			args[i] = ft_strdup(token->lexeme);
			i++;
		}
		node = node->next;
	}
	return (args);
}
