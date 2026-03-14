/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:15:09 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 16:57:16 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_environment(t_env *env);
static void	sorted_env(t_env **to_sort, int size);
static void	print_env(t_env **sorted, int size);
static int	is_valid_name(char *args);

int	builtin_export(t_exec *exec, char **args)
{
	int	exit_code;
	int	i;

	i = 1;
	exit_code = 0;
	if (!args[i])
		print_sorted_environment(exec->env_list);
	else
	{
		while (args[i])
		{
			if (is_valid_name(args[i]))
				exit_code = 1;
			else
				create_environment(&exec->env_list, args[i]);
			i++;
		}
	}
	return (exit_code);
}

static void	print_sorted_environment(t_env *env)
{
	t_env	**to_sort;
	t_env	*current;
	int		size;
	int		i;

	size = list_size(env);
	to_sort = malloc(size * sizeof(t_env *));
	if (!to_sort)
		return ;
	current = env;
	i = 0;
	while (current)
	{
		to_sort[i] = current;
		current = current->next;
		i++;
	}
	sorted_env(to_sort, size);
	print_env(to_sort, size);
	free(to_sort);
}

static void	sorted_env(t_env **to_sort, int size)
{
	int		i;
	int		j;
	t_env	*aux;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(to_sort[j]->variable, to_sort[j + 1]->variable) > 0)
			{
				aux = to_sort[j];
				to_sort[j] = to_sort[j + 1];
				to_sort[j + 1] = aux;
			}
			j++;
		}
		i++;
	}
}

static void	print_env(t_env **sorted, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted[i]->variable, STDOUT_FILENO);
		if (sorted[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(sorted[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

static int	is_valid_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("minishell: export: '", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
