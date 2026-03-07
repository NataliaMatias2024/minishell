/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:29:53 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 02:30:31 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exec_fork(t_exec *exec, t_ast *node);

int	execute_commands_handler(t_exec *exec, t_ast *node, int in_pipe)
{
	if (!exec || !node)
		return (1);
	//SE existir redirects eles devem ser processado primeiro!
	if (node->redir_lst)
	{
		//SE heredoc falhar td processo falha, por isso ele é o primeiro a ser analisado e executado
		if (check_and_run_heredoc(exec, node->redir_lst))
		{
			//so entra no if se retornar alguma coisa diferente de zero, logo deu algum erro
			//se n foi encerrado com o ctrl + c foi um erro "comum"
			if (exec->exit_status != 130)
				exec->exit_status = 1; //atualiza o status, após erros n ligados a sinais
			return (1); //encerra a execuçao dos comandos, pois heredoc ou deu erro ou foi cancelado
		}
	}
	//EXECUÇÃO DE BUILT-INS
	if (is_builtin_command(exec, node->arg))
	{
		//No geral os builtins ocorrem direto no processo pai, n usando forks
		// Aplica o resto dos REDIRECTS e concluio o Heredoc (Heredoc, <, >, >>)
		if (node->redir_lst && apply_all_redirections(exec, node->redir_lst))
		{
			//P garantir q TD a cadeia de comandos seja executada, incluindo o resto dos redirects
			//Temos q usar o STDIN e STDOU salvos ao iniciar o programa para restaurar após os redirects
			dup2(exec->backup_stdin, STDIN_FILENO);
			dup2(exec->backup_stdout, STDOUT_FILENO);
			return (1);
		}
		exec->exit_status = exec_builtin(exec, node->arg);

		//Após os redirects, como n criamos processo filho, precisamos resetar os FDS do processo pai
		dup2(exec->backup_stdin, STDIN_FILENO);
		dup2(exec->backup_stdout, STDOUT_FILENO);

		if (in_pipe)
			exit(exec->exit_status);
		return (0);
	}
	else
	{
		//Quando ocorre comandos externos temos q criar processo filho
		//SE ja estiver dentro de um fork só executa, se n cria um fork
		//EXECUÇÃO DE COMANDOS EXTERNOS
		if (in_pipe)
		{
		// Aplica o resto dos REDIRECTS e concluio o Heredoc (Heredoc, <, >, >>)
			if (node->redir_lst && apply_all_redirections(exec, node->redir_lst))
				//so entra no if se retornar alguma coisa diferente de zero, logo deu erro em algum redir
				exit(1); //se tiver dentro de um pipe ele esta em um subprocesso, por isso da exit 1
			exec_external_command(exec, node->arg);
		}
		else
		//caso contrario o execve sobrescreve o nosso minishell
			exec_fork(exec, node);
	}
	return (0);
}

static	void	exec_fork(t_exec *exec, t_ast *node)
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
		set_signals_default();
		if (node->redir_lst && apply_all_redirections(exec, node->redir_lst))
			//so entra no if se retornar alguma coisa diferente de zero, logo deu erro em algum redir
			exit(1); //se tiver dentro de um pipe ele esta em um subprocesso, por isso da exit 1

		//EXECUÇÃO COMANDOS EXTERNOS
		exec_external_command(exec, node->arg);
	}
	else if (pid > 0)
	{
		set_signals_executing();
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
		set_signals_interactive();
		// printf("exit code (executor.c) = %d\n", exit_code);
		// printf("exit code (exec->exit_status) = %d\n", exec->exit_status);
	}
}
