/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:03:40 by namatias          #+#    #+#             */
/*   Updated: 2026/02/28 21:23:59 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*check_slash(char *cmd_args);
static t_env	*find_path_node(t_env *head, char *args);
static char		*create_env_array(char *variable, char *value);

char	*create_path_array(t_env *env_list, char **cmd_args)
{
	t_env	*path_node;
	char	**paths;
	char	*exec_path;
	char	*full_path;
	int		i;

	exec_path = check_slash(cmd_args[0]);
	path_node = find_path_node(env_list, "PATH");
	if (exec_path || !path_node || !cmd_args[0])
		return (exec_path);
	paths = ft_split(path_node->value, ':');
	i = -1;
	while (paths && paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		exec_path = join_and_free(full_path, cmd_args[0]);
		//acess X_OK teste se o arquivo existe e temos permissao de executar
		if (access(exec_path, X_OK) == 0) //Retorna 0 se SIM e -1 se NAO
		{
			//achamos o path que queremos, por isso temos que:
			//liberar oq foi splitado e retornar apenas o path alvo
			free_split(paths);
			return (exec_path);
		}
		free(exec_path); //se n for o comando certo, damos free antes de testar o prox, assim n perde a ref
	}
	free_split(paths); //caso passe por tds os paths e nao ache o comando
	return (NULL);
}

static char	*check_slash(char *cmd_args)
{
	if (!cmd_args)
		return (NULL);
	if (ft_strrchr(cmd_args, '/'))
	{
		if (access(cmd_args, X_OK) == 0)
			return (ft_strdup(cmd_args));
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

char	**transform_env_list(t_env *env_list)
{
	t_env	*temp;
	char	**envp;
	int		size_env_list;
	int		i;

	size_env_list = list_size(env_list);
	envp = malloc ((size_env_list + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	temp = env_list;
	i = 0;
	while (temp)
	{
		if (temp->variable)
		{
			envp[i] = create_env_array(temp->variable, temp->value);
			if (!envp[i])
				free_split(envp);
		}
		i++;
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

static char	*create_env_array(char *variable, char *value)
{
	char	*temp;
	int		total_size;

	//garantimos espaço para as 2 strings + espaço pro terminador nulo E por =  -> variavel=value
	total_size = ft_strlen(variable) + ft_strlen(value) + 2;
	temp = malloc (total_size * sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, variable, total_size);
	ft_strlcat(temp, "=", total_size);
	ft_strlcat(temp, value, total_size);
	return (temp);
}
