/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:41:01 by namatias          #+#    #+#             */
/*   Updated: 2026/02/14 04:07:13 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	*init_environment(char **envp)
{
	int				i;
	t_environment	*head;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		create_environment(&head, envp[i]);
		i++;
	}
	// TODO: Debug, printa lista de ambiente criada, uma variavel e value por linha
	//print_list(head);
	return (head);
}

void	create_environment(t_environment	**head, char *envp)
{
	size_t			index;
	char			*variable;
	char			*variable_info;
	char			*postion_equal;

	index = 0;
	while (envp[index] && envp[index] != '=')
		index++;
	postion_equal = ft_strchr(envp, '=');

	variable = ft_substr(envp, 0, index);
	if (postion_equal != NULL)
		variable_info = ft_strdup(postion_equal + 1);
	else
		variable_info = NULL;

	if (variable)
		create_update_list_env(head, variable, variable_info);

	//TODO: Ambas as funções possuem malloc internamente, entao precisa dar free
	if (variable)
		free(variable);
	if (variable_info)
		free(variable_info);
}

char	*get_env_path(t_environment *env, char *name)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->variable, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
