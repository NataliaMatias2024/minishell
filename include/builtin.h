/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:11:07 by namatias          #+#    #+#             */
/*   Updated: 2026/02/19 02:55:43 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environment.h"
//TODO: Apagar antes do envio
//Macro definido pela limits.h, varia entre sistemas, porem é o valor mais comum
//grep -r "PATH_MAX" /usr/include/linux/limits.h -> Ve o do seu sistema
# define SIZE_PATH 4096

int	exec_builtin(t_env *environment_list, char **argv);
int	is_builtin_command(t_env **head, char **argv);
int	builtin_export(t_env **head, char **args);
int	builtin_unset(t_env **head, char **args);
int	builtin_echo(t_env **head, char **args);
int	builtin_exit(t_env **env, char **args);
int	builtin_env(t_env **head, char **args);
int	builtin_pwd(t_env **head, char **args);
int	builtin_cd(t_env **env, char **args);

#endif