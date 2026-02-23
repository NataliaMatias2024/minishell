/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:46:12 by namatias          #+#    #+#             */
/*   Updated: 2026/02/23 00:02:15 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_path_node(t_env *head, char *args);
static char		**transform_env_list(t_env *env_list);
static char		*create_env_array(char *variable, char *value);
static char		*create_path_array(t_env *env_list, char **cmd_args);

int	exec_external_command(t_env *env_list, char **cmd_args)
{
	char	*pathname;
	char	**envp;

	pathname = create_path_array(env_list, cmd_args);
	if (!pathname) //comando n existe ou n tem permissao de execuçao 
	{
		ft_putstr_fd("minishell: Command '", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putendl_fd("' not found", STDERR_FILENO);
		// g_exit_status = 127; //TODO: 127 é o codigo padrao do linux para comando n encontrado
		return (-1);
	}
	envp = transform_env_list(env_list);
	execve(pathname, cmd_args, envp);
	free(pathname);
	return (0);
}

static char	*create_path_array(t_env *env_list, char **cmd_args)
{
	t_env	*path_node;
	char	**paths;
	char	*exec_path;
	char	*full_path;
	int		i;

	path_node = find_path_node(env_list, "PATH");
	//caso o usuario tenha dado unset no path
	if (!path_node)
		return (NULL);
	paths = ft_split(path_node->value, ':');
	i = 0;
	while (paths [i])
	{
		full_path = ft_strjoin(paths[i], "/");
		exec_path = join_and_free(full_path, cmd_args[0]);
		//acess X_OK teste se o arquivo existe e temos permissao de executar
		if (access(exec_path, X_OK) == 0) //Retorna 0 se SIM e -1 se NAO
		{
			//achamos o path que queremos, liberados oq foi splitado e retornamos apenas o path alvo
			free_split(paths);
			return (exec_path);
		}
		free(exec_path); //se n for o comando certo, damos free antes de testar o prox, assim n perde a ref
		i++;
	}
	free_split(paths); //caso passe por tds os paths e nao ache o comando
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

static char	**transform_env_list(t_env *env_list)
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
