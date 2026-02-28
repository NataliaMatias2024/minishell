/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:29:53 by namatias          #+#    #+#             */
/*   Updated: 2026/02/28 11:00:12 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exec_fork(t_exec *exec, char **cmd_args);

void	execute_handler(t_exec *exec, char **cmd_args)
{
	//EXECUÇÃO DE BUILT-INS
	if (is_builtin_command(&exec->env_list, cmd_args))
		exec->exit_status = exec_builtin(exec->env_list, cmd_args);
	else
	{
		exec_fork(exec, cmd_args);
	}
}

static	void	exec_fork(t_exec *exec, char **cmd_args)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	status = 0;
	exit_code = 0;
	pid = fork();
	if (pid < 0)
		perror("minishell: fork fail");
	else if (pid == 0) //processo filho
	{
		//EXECUÇÃO COMANDOS EXTERNOS
		exec_external_command(exec, cmd_args);
	}
	else if (pid > 0)
	{
		//para acessar o status usamos MACROS da biblioteca sys/wait.h, q traduz o valor preenchido pelo waitpid
		waitpid(pid, &status, 0);
		//SE o processo filho terminar via exit (saida padrao)
		if (WIFEXITED(status)) //Wait IF EXITED -> retorna verdadeiro se o processo terminou com return ou exit
			exit_code = WEXITSTATUS(status); //Pega o estatus de saida real, o n de 0 a 255 é convertido pro 0, 1 , 127 da funçao filho
		//SE o processo filho terminar devido algum sinal (ctrl + C)
		else if (WIFSIGNALED(status)) //Wait IF SIGNALED -> returna vdd se o filho encerrou por algum sinal
	//SIGINT (Ctrl+C): Sinal nº 2. Resultado: $128 + 2 = 130 , o 128 é para isolar oq é status vindos d sinal e oq é vindo do codigo como um exit(2)
			exit_code = 128 + WTERMSIG(status); // extrai o numero do sinal e soma com 128 (padrao do linux)
		exec->exit_status = exit_code;
		// printf("exit code (executor.c) = %d\n", exit_code);
		// printf("exit code (exec->exit_status) = %d\n", exec->exit_status);
	}
}
