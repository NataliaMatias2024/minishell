/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:09:33 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 22:22:32 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
