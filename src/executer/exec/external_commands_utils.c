/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:03:40 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 22:04:20 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*check_slash(char *args);
static t_env	*find_path_node(t_env *head, char *args);

char	*create_path_array(t_env *env_list, char **args)
{
	t_env	*path_node;
	char	**paths;
	char	*exec_path;
	char	*full_path;
	int		i;

	exec_path = check_slash(args[0]);
	path_node = find_path_node(env_list, "PATH");
	if (exec_path || !path_node || !args[0])
		return (exec_path);
	paths = ft_split(path_node->value, ':');
	i = -1;
	while (paths && paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		exec_path = join_and_free(full_path, args[0]);
		if (access(exec_path, X_OK) == 0)
		{
			free_split(paths);
			return (exec_path);
		}
		free(exec_path);
	}
	free_split(paths);
	return (NULL);
}

static char	*check_slash(char *args)
{
	if (!args)
		return (NULL);
	if (ft_strrchr(args, '/'))
	{
		if (access(args, X_OK) == 0)
			return (ft_strdup(args));
	}
	return (NULL);
}

static t_env	*find_path_node(t_env *head, char *args)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strcmp(temp->variable, args) == 0)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	return (temp);
}

char	*create_env_array(char *variable, char *value)
{
	char	*temp;
	int		total_size;

	if (!value)
		return (ft_strdup(variable));
	total_size = ft_strlen(variable) + ft_strlen(value) + 2;
	temp = malloc (total_size * sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, variable, total_size);
	ft_strlcat(temp, "=", total_size);
	ft_strlcat(temp, value, total_size);
	return (temp);
}
