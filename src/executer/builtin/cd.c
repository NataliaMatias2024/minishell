/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:18:15 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 17:06:22 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*target_path(t_env **env, char **args);
static int	execute_chdir(char *target, char *old_pwd);
static int	handle_max_args(char **args);

int	builtin_cd(t_exec *exec, char **args)
{
	char	pwd[SIZE_PATH];
	char	*old_pwd;
	char	*target;
	int		exit_status;

	exit_status = handle_max_args(args);
	if (getcwd(pwd, SIZE_PATH))
		old_pwd = ft_strdup(pwd);
	else
		old_pwd = ft_strdup("");
	target = target_path(&exec->env_list, args);
	if (!target)
	{
		free(old_pwd);
		return (1);
	}
	if (execute_chdir(target, old_pwd) != 0)
		return (1);
	create_update_list_env(&exec->env_list, "OLDPWD", old_pwd);
	free(old_pwd);
	if (getcwd(pwd, SIZE_PATH))
		create_update_list_env(&exec->env_list, "PWD", pwd);
	return (exit_status);
}

static int	handle_max_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static char	*target_path(t_env **env, char **args)
{
	char	*target;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		target = get_env_path(env, "HOME");
		if (target == NULL)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
	}
	else if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_path(env, "OLDPWD");
		if (target == NULL)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (NULL);
		}
		ft_printf("%s\n", target);
	}
	else
		target = args[1];
	return (target);
}

static	int	execute_chdir(char *target, char *old_pwd)
{
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	return (0);
}
