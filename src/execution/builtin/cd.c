/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:18:15 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 03:35:51 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*target_path(t_env **env, char **args);
static char	*get_env_path(t_env **env, char *name);
static int	execute_chdir(char *target, char *old_pwd);
static int	handle_max_args(char **args);

int	builtin_cd(t_env **env, char **args)
{
	char	pwd[SIZE_PATH];
	char	*old_pwd;
	char	*target;
	int		exit_status;

	//se receber info a + retornar 1
	exit_status = handle_max_args(args);
	//verificar o local atual e salvar antes de mover na variavel caminho antigo
	if (getcwd(pwd, SIZE_PATH))
		old_pwd = ft_strdup(pwd);
	else
		old_pwd = ft_strdup("");
	//verificar se diretorio indicado existe e salvar seu caminho
	target = target_path(env, args);
	if (!target)
	{
		free(old_pwd);
		return (1);
	}
	//chamar chdir(objetivo), pois ele procura o nome ou caminho no ambiente retornando 0 ou -1 (erro)
	if (execute_chdir(target, old_pwd) != 0)
		return (1);
	//atualizar ambiente e dar free no caminho antigo (antes do chdir) e att o novo (após chdir)
	create_update_list_env(env, "OLDPWD", old_pwd);
	free(old_pwd);
	if (getcwd(pwd, SIZE_PATH))
		create_update_list_env(env, "PWD", pwd);
	return (exit_status);
}

static int	handle_max_args(char **args)
{
	//se receber info a + retornar erro de muitos argumentos
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static char	*target_path(t_env **env, char **args)
{
	//verificar se recebemos cd + nome de onde ir
	//se receber apenas cd OU  cd ~ mudar para home (getenv("HOME"))
	//se receber cd - , mudar para OLDPWD
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

static char	*get_env_path(t_env **env, char *name)
{
	t_environment	*temp_env;

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

static	int	execute_chdir(char *target, char *old_pwd)
{
	//se retornar qualquer coisa q nao 0 é pq deu erro, imprimir erro na tela, dar free e finalizar
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	return (0);
}
