/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:08:17 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/28 11:08:26 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *lex)
{
	char	*msg;

	msg = "minishell: syntax error near unexpected token `";
	if (!lex)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	write(2, lex, ft_strlen(lex));
	ft_putstr_fd("' \n", STDERR_FILENO);
}
