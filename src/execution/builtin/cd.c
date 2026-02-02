/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:18:15 by namatias          #+#    #+#             */
/*   Updated: 2026/02/02 18:57:10 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_cd(char **args)
{
	int	status;
	//se receber info a + retornar erro de muitos argumentos
		//verificar o local atual e salvar(caminho antigo)
		//"chamar chdir(objetivo), pois ele procura o nome no ambiente retornando 0 no sucesso e -1 no erro
	//atualizar ambiente, manter o caminho antigo pego antes do chdir e o novo caminho pwd
	//verificar se recebemos cd + nome de onde ir
	//se receber apenas cd mudar para home (getenv("HOME"))
	if ((ft_strcmp(*args, "cd") == 0) || (ft_strcmp(*args, "~") == 0))
	{
		//TODO: caso home n exista retornar erro
		status = chdir("/HOME");
	}
	return (status);
}
