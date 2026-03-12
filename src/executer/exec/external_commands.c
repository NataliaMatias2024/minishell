/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:46:12 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 22:05:19 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_env_list(t_env *env_list);
char		**transform_env_list(t_env *env_list);

void	exec_external_command(t_exec *exec, char **cmd_args)
{
	char	*pathname;
	char	**envp;

	pathname = create_path_array(exec->env_list, cmd_args);
	if (!pathname)
	{
		ft_putstr_fd("minishell: Command '", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putendl_fd("' not found", STDERR_FILENO);
		free(pathname);
		free_clean_all(exec);
		exit(127);
	}
	envp = transform_env_list(exec->env_list);
	execve(pathname, cmd_args, envp);
	perror("minishell");
	free(pathname);
	free_split(envp);
	free_clean_all(exec);
	exit(126);
}

char	**transform_env_list(t_env *env_list)
{
	t_env	*temp;
	char	**envp;
	int		i;

	envp = malloc ((size_env_list(env_list) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	temp = env_list;
	while (temp)
	{
		if (temp->value != NULL)
		{
			envp[i] = create_env_array(temp->variable, temp->value);
			if (!envp[i])
			{
				free_split(envp);
				return (NULL);
			}
			i++;
		}
		temp = temp->next;
	}
	envp[i] = NULL;
	return (envp);
}

static	int	size_env_list(t_env *env_list)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = env_list;
	while (temp)
	{
		if (temp->value != NULL)
			i++;
		temp = temp->next;
	}
	return (i);
}
