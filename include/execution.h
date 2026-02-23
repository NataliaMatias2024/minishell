/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:13:52 by namatias          #+#    #+#             */
/*   Updated: 2026/02/22 23:47:18 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>

# include "environment.h"
# include "builtin.h"
# include "expansion.h"

int		exec_commands(t_env *env_list, char **cmd_args);
int		exec_external_command(t_env *env_list, char **cmd_args);
int		is_external_command(t_env *env_list, char **cmd_args);

char	*get_env_path(t_env **env, char *name);
char	**tokens_to_argv(t_dlist *tklst);
void	free_split(char **splited);
int		ft_is_space(char *line);

#endif