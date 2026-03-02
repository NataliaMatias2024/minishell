/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:54:45 by namatias          #+#    #+#             */
/*   Updated: 2026/03/02 19:49:14 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}							t_env;

t_env	*init_environment(char **envp);
t_env	*create_environment_node(char *var, char *var_info);

void	create_environment(t_env **head, char *envp);
void	create_update_list_env(t_env **head, char *var, char *var_info);

int		list_size(t_env *head);

void	deleting_list(t_env **head);
void	deleting_node(t_env *to_delete);
// void	clear_child_process(t_exec *exec);

#endif
