/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:03:35 by namatias          #+#    #+#             */
/*   Updated: 2026/02/19 03:35:09 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

char	*remove_quotes(char *lexeme);
char	*join_and_free(char *s1, char *s2);
int		quote_state(char lexeme, int current_state);
int		expand_variable(t_env *env, t_dlist **tklst);

#endif
