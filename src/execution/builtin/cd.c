/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:18:15 by namatias          #+#    #+#             */
/*   Updated: 2026/02/07 02:00:37 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char *target_path(t_environment *env, char **args);

int	builtin_cd(t_environment *env, char **args)
{
	char	pwd[SIZE_PATH];
	char	*old_pwd;
	char	*new_pwd;
	char	*target;

	//se receber info a + retornar erro de muitos argumentos
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}

	//verificar o local atual e salvar(caminho antigo)
	if(getcwd(pwd, SIZE_PATH))
		old_pwd = ft_strdup(pwd);
	else
		old_pwd = ft_strdup("");
	target = target_path(env, args);
	if (!target)
		return (1);

	//chamar chdir(objetivo), pois ele procura o nome no ambiente retornando 0 no sucesso e -1 no erro
	if (chdir(target) != 0)
	{
			perror("minishell:  cd");
			return (1);
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_printf("%s\n", old_pwd);

	if (getcwd(pwd, SIZE_PATH))
		new_pwd = ft_strdup(pwd);
	else
		new_pwd = ft_strdup("");

	//atualizar ambiente, manter o caminho antigo pego antes do chdir e o novo caminho pwd
	create_update_list_env(&env, "OLDPWD", old_pwd);
	free(old_pwd);
	create_update_list_env(&env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

static	char *target_path(t_environment *env, char **args)
{
	//verificar se recebemos cd + nome de onde ir
	//se receber apenas cd OU  cd ~ mudar para home (getenv("HOME"))
	//se receber cd - , mudar para OLDPWD
	char	*target;
	
	if (!args[1] ||  ft_strcmp(args[1], "~") == 0)
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
	}
	else
		target = args[1];
	return (target);
}
