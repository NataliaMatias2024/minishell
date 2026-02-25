/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:03:35 by namatias          #+#    #+#             */
/*   Updated: 2026/02/25 01:15:11 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/* FORWARD DECLARATION */
/* Isso avisa o compilador: "Existe uma struct chamada s_executor que chamamos de t_exec". */
/* Assim posso deixar os includes antes da struct no executin.h como a norminette exige */
typedef struct s_executor t_exec;

char	*remove_quotes(char *lexeme);
char	*join_and_free(char *s1, char *s2);
int		quote_state(char lexeme, int current_state);
int		expand_variable(t_exec *exec, t_dlist **tklst);

#endif
