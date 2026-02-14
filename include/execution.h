/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:54:45 by namatias          #+#    #+#             */
/*   Updated: 2026/02/14 04:09:44 by namatias         ###   ########.fr       */
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
#include <errno.h>
#include <string.h>

//Macro definido pela limits.h, varia entre sistemas, porem é o valor mais comum
//grep -r "PATH_MAX" /usr/include/linux/limits.h -> Ve o do seu sistema
# define SIZE_PATH 4096

typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}							t_environment;

t_environment	*detach_node(t_environment **previus, t_environment *target_node);
t_environment	*create_environment_node(char *var, char *var_info);
t_environment	*init_environment(char **envp);
int				list_size(t_environment *head);
void			create_update_list_env(t_environment **head, char *var, char *var_info);
void			create_environment(t_environment	**head, char *envp);
char			*get_env_path(t_environment *env, char *name);
void			print_list(t_environment *head);

void			deleting_node(t_environment *to_delete);
void 			deleting_list(t_environment **head);

int				ft_is_valid(char *string);
void 			free_split(char **splited);

int				builtin_export(t_environment **head, char **args);
int 			builtin_unset(t_environment **head, char **args);
int				builtin_exit(t_environment **env, char **args);
int				builtin_env(t_environment *head, char **args);
int				builtin_cd(t_environment *env, char **args);
int				builtin_echo(char **args);
int				builtin_pwd(char **args);

#endif

