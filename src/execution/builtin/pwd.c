/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:50:32 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 02:57:05 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_environment **head, char **args)
{
	char	pwd[SIZE_PATH];

	(void)args;
	(void)head;
	if (getcwd(pwd, SIZE_PATH))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (0);
	}
	else
		ft_putendl_fd("pwd: error retrieving current directory", STDERR_FILENO);
	return (1);
}
