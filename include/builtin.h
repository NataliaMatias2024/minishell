/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:11:07 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 22:35:58 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "execution.h"
# define SIZE_PATH 4096

typedef struct s_executor	t_exec;

int		is_builtin_command(t_exec *exec, char **args);
int		exec_builtin(t_exec *exec, char **args);

int		builtin_export(t_exec *exec, char **args);
int		builtin_unset(t_exec *exec, char **args);
int		builtin_echo(t_exec *exec, char **args);
int		builtin_exit(t_exec *exec, char **args);
int		builtin_env(t_exec *exec, char **args);
int		builtin_pwd(t_exec *exec, char **args);
int		builtin_cd(t_exec *exec, char **args);

#endif