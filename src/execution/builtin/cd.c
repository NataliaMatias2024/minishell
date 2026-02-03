/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:18:15 by namatias          #+#    #+#             */
/*   Updated: 2026/02/03 18:36:44 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_cd(char **args)
{
	int		status;
	char	pwd[SIZE_PATH];
	char	*old_pwd;
	char	*target;

	status = 0;
	//TODO: verifica oq foi recebido
	int i = 0;
	while (args[i])
	{
		printf("Arg[%d] = %s\n", i,args[i]);
		i++;
	}
	//verificar se recebemos cd + nome de onde ir
	if (!args[1])
	{
		
	}
	//se receber info a + retornar erro de muitos argumentos
	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	//verificar o local atual e salvar(caminho antigo)
	getcwd(pwd, SIZE_PATH);
	old_pwd = ft_strdup(pwd);

	//se receber apenas cd mudar para home (getenv("HOME"))
	//"chamar chdir(objetivo), pois ele procura o nome no ambiente retornando 0 no sucesso e -1 no erro
	if (chdir(target) != 0)
			perror("Error");
	//atualizar ambiente, manter o caminho antigo pego antes do chdir e o novo caminho pwd

	return (status);
}
