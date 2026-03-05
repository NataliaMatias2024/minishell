/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:00:38 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 22:17:16 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid(char *string);

int	builtin_exit(t_exec *exec, char **args)
{
	int	exit_flag;

	exit_flag = 0;
	if (args[1])
	{
		if (!ft_is_valid(args[1]))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("exit: numeric argument required.", STDERR_FILENO);
			free_clean_all(exec);
			exit(2);
		}
		else if (args[2])
		{
			ft_putendl_fd("exit: too many arguments.", STDERR_FILENO);
			return (1);
		}
		exit_flag = (ft_atoi(args[1]) % 256);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_clean_all(exec);
	exit(exit_flag % 256);
	return (0);
}

static int	ft_is_valid(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '-' || string[i] == '+')
		i++;
	if (!string[i])
		return (0);
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_clean_all(t_exec *exec)
{
	if (!exec)
		return ;
	//Se tiver lista de ambiente
	if (exec->env_list)
		deleting_list(&(exec->env_list));
	//Se os fds existirem e tiverem fd salvos
	if (exec->backup_stdin >= 0)
		close(exec->backup_stdin);
	if (exec->backup_stdout >= 0)
    	close(exec->backup_stdout);
	//limpa o historico do readline
	rl_clear_history();
	//Se existir a arvore da free e limpa
	if (exec->ast_root)
		printf("limpando e liberando arvore\n");
		//TODO: funçao de free do parser;
}
