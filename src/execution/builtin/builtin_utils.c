/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:21:09 by namatias          #+#    #+#             */
/*   Updated: 2026/02/03 17:25:13 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid(char *string)
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

int	ft_is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32)
			return (1);
		i++;
	}
	return (0);
}
