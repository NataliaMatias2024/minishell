/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:54:45 by namatias          #+#    #+#             */
/*   Updated: 2026/02/15 04:40:01 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}							t_environment;

t_environment	*init_environment(char **envp);
void			create_environment(t_environment **head, char *envp);
t_environment	*create_environment_node(char *var, char *var_info);
void			create_update_list_env(t_environment **head,
					char *var, char *var_info);

int				list_size(t_environment *head);

void			deleting_list(t_environment **head);
void			deleting_node(t_environment *to_delete);

#endif
