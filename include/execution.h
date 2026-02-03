/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:54:45 by namatias          #+#    #+#             */
/*   Updated: 2026/02/03 18:43:06 by namatias         ###   ########.fr       */
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
//Macro definido pela limits.h, varia entre sistemas, porem é o valor mais comum
//grep -r "PATH_MAX" /usr/include/linux/limits.h -> Ve o do seu sistema
# define SIZE_PATH 4096

typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}							t_environment;

t_environment	*init_environment(char **envp);
void			create_environment_array(t_environment	**head, char *envp);
t_environment	*create_environment_node(char *var, char *var_info);
void			create_list_env(t_environment **head, char *var, char *var_info);
void			print_list_teste(t_environment *head);
char			*get_env_path(t_environment *env, char *name);

int				ft_is_valid(char *string);
int				builtin_pwd(char **args);
int				builtin_cd(t_environment *env, char **args);
int				builtin_exit(char **args);

#endif

