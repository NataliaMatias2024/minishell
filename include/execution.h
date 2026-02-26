/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:13:52 by namatias          #+#    #+#             */
/*   Updated: 2026/02/25 13:59:10 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define _GNU_SOURCE
# include <fcntl.h>
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
# include "token.h"
# include "builtin.h"
# include "expansion.h"

typedef struct s_executor
{
	t_env	*env_list;
	int		exit_status;
	int		saved_stdin;
	int		saved_stdout;
}			t_exec;

void	execute_handler(t_exec *exec, char **cmd_args);
void	exec_external_command(t_exec *exec, char **cmd_args);

char	**transform_env_list(t_env *env_list);
char	*create_path_array(t_env *env_list, char **cmd_args);

int		ft_is_space(char *line);
void	free_split(char **splited);
char	**tokens_to_argv(t_dlist *tklst);
char	*get_env_path(t_env **env, char *name);

#endif