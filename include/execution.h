/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:54:45 by namatias          #+#    #+#             */
/*   Updated: 2026/02/02 18:52:20 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <limits.h>
//Macro definido pela limits.h, varia entre sistemas, porem é o valor mais comum
//grep -r "PATH_MAX" /usr/include/linux/limits.h -> Ve o do seu sistema
# define SIZE_PATH 4096

int		ft_is_valid(char *string);
int		builtin_pwd(void);
int		builtin_cd(char **args);
int		builtin_exit(char **args);

#endif

