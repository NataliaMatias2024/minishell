/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:18:15 by namatias          #+#    #+#             */
/*   Updated: 2026/01/28 17:53:47 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_cd(char **args)
{
	//se receber info a + retornar erro de muitos argumentos
	//se receber apenas cd mudar para home (getenv("HOME"))
		//caso home n exista retornar erro
	//verificar se recebemos cd + nome de onde ir
		//verificar o local atual e salvar(caminho antigo)
		//"chamar chdir(objetivo), pois ele procura o nome no ambiente retornando 0 no sucesso e -1 no erro
	//atualizar ambiente, manter o caminho antigo pego antes do chdir e o novo caminho pwd
	/*
		typedef struct s_env
		{
			char            *key; // Ex: "PWD"
			char            *value; // Ex: "/home/user"
			struct s_env    *next;
		}   t_env;
   */
}
