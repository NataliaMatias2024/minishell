/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:41:01 by namatias          #+#    #+#             */
/*   Updated: 2026/02/09 11:10:36 by namatias         ###   ########.fr       */
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
		create_environment_array(&head, envp[i]);
		i++;
	}
	// TODO: Debug, printa lista de ambiente criada, uma variavel e value por linha
	//print_list(head);
	return (head);
}

void	create_environment_array(t_environment	**head, char *envp)
{
	int				index;
	char			*variable;
	char			*variable_info;

	index = 0;
	while (envp[index] && envp[index] != '=')
		index++;

	variable = ft_substr(envp, 0, index);
	variable_info = ft_strdup(envp + index + 1);

	if (variable && variable_info)
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
