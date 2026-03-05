/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:11:07 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 22:01:44 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "execution.h"
//TODO: Apagar antes do envio
//Macro definido pela limits.h, varia entre sistemas, porem é o valor mais comum
//grep -r "PATH_MAX" /usr/include/linux/limits.h -> Ve o do seu sistema
# define SIZE_PATH 4096

/* FORWARD DECLARATION */
/* Isso avisa o compilador: "Existe uma struct chamada s_executor que chamamos de t_exec". */
/* Assim posso deixar os includes antes da struct no executin.h como a norminette exige */
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
void	free_clean_all(t_exec *exec);

#endif