/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:15:09 by namatias          #+#    #+#             */
/*   Updated: 2026/02/14 14:37:10 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_sorted_environment(t_environment *env);
static void sorted_env(t_environment **to_sort, int size);
static void	print_env(t_environment **sorted, int size);
static int is_valid_name(char *args);

int	builtin_export(t_environment **head, char **args)
{
	int	exit_code;
	int	i;

	i = 1;
	exit_code = 0;
	//SE apenas export for digitado retornar lista de env 
	//EM ORDEM ALFABETICA no formato "declare -x VARIAVEL"
	if(!args[i])
		print_sorted_environment(*head);
	else
	{
		//Funciona para mais de uma variavel por vez (EX: export VAR1=val1 VAR2=val2 VAR3) deve funcionar
		while(args[i])
		{
			if (is_valid_name(args[i]))
				exit_code = 1;
			else
			{
				//Sinais de = multiplos, o primeiro = funciona como divisor entre NAME e VALUE os d+ fazem parte do valur
				//EX: export VAR=valor=extra, O variable é VAR e o value é valor=extra
				//SE for acrescentado apenas NAME -> value é realmente nulo e nao aparece na lista env MAS aparece na export
				//SE for acrescentado apenas NAME= -> value aparece como uma string vazia "" e aparece na lista env e export
				//APOS tudo isso o env deve ser atualizado.
				create_environment(head, args[i]);
			}
			i++;
		}
	}
	return (exit_code);
}

static void print_sorted_environment(t_environment *env)
{
	t_environment	**to_sort;
	t_environment	*current;
	int				size;
	int				i;

	size = list_size(env);
	printf("Size = %d\n", size);
	to_sort = malloc(size * sizeof(t_environment *));
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

static void sorted_env(t_environment **to_sort, int size)
{
//Bubble sort, ordena da forma mais simples, do ultimo espaço para o primeiro
	int				i;
	int				j;
	t_environment	*auxiliar;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(to_sort[j]->variable, to_sort[j + 1]->variable) > 0)
			{
				auxiliar = to_sort[j];
				to_sort[j] = to_sort[j + 1];
				to_sort[j + 1] = auxiliar;
			}
			j++;
		}
		i++;
	}
}

static void	print_env(t_environment **sorted, int size)
{
	//SE apenas export for digitado retornar lista de env 
	//EM ORDEM ALFABETICA no formato "declare -x VARIAVEL"
	int				i;

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

static int is_valid_name(char *str)
{
	//Sao validos nomes que comecem com uma letra ou um _ (ex: 1var, var-name -> retornam erro)
	//SE name nao for valido retorna status = 1 e erro: not a valid identifier
	int	i;

	i = 0;
	if(!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	while(str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) &&  str[i] != '_')
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
