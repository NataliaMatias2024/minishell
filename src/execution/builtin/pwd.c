/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:50:32 by namatias          #+#    #+#             */
/*   Updated: 2026/01/26 18:06:05 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	pwd[SIZE_PATH];

	if (getcwd(pwd, SIZE_PATH))
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (0);
	}
	ft_putendl_fd("pwd: error retrieving current directory", STDERR_FILENO);
	return (1);
}
