/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:42:44 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 03:22:08 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*temp;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

int	quote_state(char lexeme, int current_state)
{
	if (lexeme == '\'' && current_state == 0)
		return (1);
	else if (lexeme == '\"' && current_state == 0)
		return (2);
	else if (lexeme == '\'' && current_state == 1)
		return (0);
	else if (lexeme == '\"' && current_state == 2)
		return (0);
	return (current_state);
}

char	*remove_quotes(char *lexeme)
{
	int		i;
	int		old_status;
	int		current_status;
	char	*removed;
	char	temp[2];

	i = 0;
	temp[1] = '\0';
	removed = ft_strdup("");
	current_status = 0;
	while (lexeme[i])
	{
		old_status = current_status;
		current_status = quote_state(lexeme[i], current_status);
		if (current_status != old_status)
			i++;
		else
		{
			temp[0] = lexeme[i];
			removed = join_and_free(removed, temp);
			i++;
		}
	}
	return (removed);
}
