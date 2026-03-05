/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:52:54 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 22:09:44 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_exit_status(t_exec *exec);

//TODO: Testar quando parser ficar pronto
void	exec_pipe(t_exec *exec, t_ast *node)
{
	int		fds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fds) < 0)
		return ;

	//executar fork pra esquerda
	pid_left = fork();
	if (pid_left == 0) //processo filho da direita
	{
		//Pega as informaçoes resultados do imput padrao e passa pelo STDOUT para a entrada do pipe a direita
		//Por isso redirecionamos Standard Output (STDOUT) p a ponta de escrita do pipe, pois vamos escrever nele (fd[1])
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec_ast(exec, node->left, 1);
		exit(exec->exit_status);
	}
	//executar fork pra direita
	pid_right = fork();
	if (pid_right == 0) //processo filho da direita
	{
		// | comandos do fork da direita
		//Recebe o resultado/texto da esq como se fosse um imput padrao, por isso redirecionnamos o fd d saida p o d entrada
		//No pipe a ponta de leitura (fd[0]) é por onde o dado SAI do pipe e entra no processo.
		//Por isso temos que redireciona o fd[0] (saida do pipe) para o STDIN (entrada de leitura do precesso) 
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		exec_ast(exec, node->right, 1);
		exit(exec->exit_status);
	}
	//a partir daqui será o processo pai
	//Como pipe foi chamado dentro do fork nao precisamos restaurar os canais de leitura e escrita do pai
	//MAS precisamos fechar os fds do pipe pois nao iremos usar mais
	close(fds[0]);
	close(fds[1]);
	//Tbm precisamos adicionar a espera e captura dos status dos processos filhos. 
	// Esperamos o da esquerda para ele não virar zumbi (o processo termina mas o sistema n recebe o aviso)
	waitpid(pid_left, NULL, 0); 

	// Esperamos o da direita e guardamos o status dele para alimentar a variavel $?
	waitpid(pid_right, &exec->exit_status, 0);

	// Antes de alimentar a variavel precisamos tratar o status recebido, transformando ele noTratamos o status da direita para pegar o valor real (0-255)
	update_exit_status(exec); //TODO: SINAIS, TESTAR
	printf("exit code (pipe.c) = %d\n", exec->exit_status);
}

static void	update_exit_status(t_exec *exec)
{
	int	status;
	int	exit_code;

	status = exec->exit_status;
	//SE o processo filho terminar via exit (saida padrao)
	if (WIFEXITED(status)) //Wait IF EXITED -> retorna verdadeiro se o processo terminou com return ou exit
		exit_code = WEXITSTATUS(status); //Pega o estatus de saida real, o n de 0 a 255 é convertido pro 0, 1 , 127 da funçao filho
	//SE o processo filho terminar devido algum sinal (ctrl + C)
	else if (WIFSIGNALED(status)) //Wait IF SIGNALED -> returna vdd se o filho encerrou por algum sinal
	//SIGINT (Ctrl+C): Sinal nº 2. Resultado: $128 + 2 = 130 , o 128 é para isolar oq é status vindos d sinal e oq é vindo do codigo como um exit(2)
		exit_code = 128 + WTERMSIG(status); // extrai o numero do sinal e soma com 128 (padrao do linux)
	exec->exit_status = exit_code;
}
