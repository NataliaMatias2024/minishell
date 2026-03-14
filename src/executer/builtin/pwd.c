/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:50:32 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 16:57:44 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_exec *exec, char **args)
{
	char	pwd[SIZE_PATH];

	(void)args;
	(void)exec;
	if (getcwd(pwd, SIZE_PATH))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (0);
	}
	else
		ft_putendl_fd("pwd: error retrieving current directory", STDERR_FILENO);
	return (1);
}
