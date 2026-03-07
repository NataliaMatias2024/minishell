/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:44:35 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 02:14:25 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
#define SIGNAL_H

void	set_signals_ignore(void);
void	set_signals_default(void);
void	set_signals_executing(void);
void	set_signals_interactive(void);
void	handle_signals_executing(int signal);
void	handle_signals_interactive(int signal);


#endif