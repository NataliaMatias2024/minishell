/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 04:11:07 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 04:39:00 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environment.h"
//TODO: Apagar antes do envio
//Macro definido pela limits.h, varia entre sistemas, porem é o valor mais comum
//grep -r "PATH_MAX" /usr/include/linux/limits.h -> Ve o do seu sistema
# define SIZE_PATH 4096

int	exec_builtin(t_environment *environment_list, char **argv);
int	is_builtin_command(t_environment **head, char **argv);
int	builtin_export(t_environment **head, char **args);
int	builtin_unset(t_environment **head, char **args);
int	builtin_echo(t_environment **head, char **args);
int	builtin_exit(t_environment **env, char **args);
int	builtin_env(t_environment **head, char **args);
int	builtin_pwd(t_environment **head, char **args);
int	builtin_cd(t_environment **env, char **args);

#endif