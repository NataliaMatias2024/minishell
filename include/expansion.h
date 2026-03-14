/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:03:35 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 03:25:18 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

typedef struct s_executor	t_exec;

char	*get_name(char *str, int *i);
char	*remove_quotes(char *lexeme);
char	*join_and_free(char *s1, char *s2);
int		quote_state(char lexeme, int current_state);
int		expand_variable(t_exec *exec, t_dlist **tklst);
char	*handle_dollar(t_exec *exec, char *lexeme, int *i, char *analyzed);

#endif
