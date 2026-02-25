/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:46:12 by namatias          #+#    #+#             */
/*   Updated: 2026/02/24 23:16:53 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_external_command(t_exec *exec, char **cmd_args)
{
	char	*pathname;
	char	**envp;

	pathname = create_path_array(exec->env_list, cmd_args);
	if (!pathname) //comando n existe ou n tem permissao de execuçao
	{
		ft_putstr_fd("minishell: Command '", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putendl_fd("' not found", STDERR_FILENO);
		//127 é o codigo padrao do linux para comando n encontrado, como exec é chamado no processo filho
		//podemos dar exit direto, e o valor ja vai pra a variavel global //TODO
		exit(127);
	}
	envp = transform_env_list(exec->env_list);
	execve(pathname, cmd_args, envp);
	//ao funcionar as proximas linhas nao sao executas, o programa para aqui! e volta pro processo que chamou o exec
	//no caso nossa main q estara em looping até algum sinal de interromper for recebido.
	//ao achar o comando porem dar algum erro na execuçao, ai sim essas linhas entram no jogo
	perror("minishell");
	free(pathname);
	free_split(envp);
	exit(126); //assim como 127, 126 é um codigo padrao do linux. Usado quando o caminho existe porem o exec nao 
	//consegue rodar, o moditivo especifico varia, mas será explicado pelo perror anterior.
}
