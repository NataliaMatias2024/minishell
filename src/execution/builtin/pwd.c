/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:50:32 by namatias          #+#    #+#             */
/*   Updated: 2026/02/03 14:12:55 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **args)
{
	char	pwd[SIZE_PATH];

	if (args[1])
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
	else if (getcwd(pwd, SIZE_PATH))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (0);
	}
	else
		ft_putendl_fd("pwd: error retrieving current directory", STDERR_FILENO);
	return (1);
}
