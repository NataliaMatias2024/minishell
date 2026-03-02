/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:52:54 by namatias          #+#    #+#             */
/*   Updated: 2026/03/02 19:49:04 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: Testar quando parser ficar pronto
// int	exec_pipe(t_exec *exec/*, t_ast *tree*/)
// {
// 	int		fds[2];
// 	int		status;
// 	pid_t	pid_left;
// 	pid_t	pid_right;

// 	if (pipe(fds) < 0)
// 	{
// 		perror("minishell: pipe");
// 		exec->exit_status = 1;
// 		return (1);
// 	}
// 	//executar fork pra direita
// 	pid_right = fork();
// 	if (pid_right == 0) //processo filho da direita
// 	{
// 		// | comandos do fork da direita
// 		//Recebe o resultado/texto da esq como se fosse um imput padrao, por isso redirecionnamos o fd d saida p o d entrada
// 		//No pipe a ponta de leitura (fd[0]) é por onde o dado SAI do pipe e entra no processo.
// 		//Por isso temos que redireciona o fd[0] (saida do pipe) para o STDIN (entrada de leitura do precesso) 
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[1]);
// 		close(fds[0]);
// 		//executa arvore (t_ast->right);
//		//clear_child_process(exec);
// 		exit(exec->exit_status);
// 	}
// 	//executar fork pra esquerda
// 	pid_left = fork();
// 	if (pid_left == 0) //processo filho da direita
// 	{
// 		//Pega as informaçoes resultados do imput padrao e passa pelo STDOUT para a entrada do pipe a direita
// 		//Por isso redirecionamos Standard Output (STDOUT) p a ponta de escrita do pipe, pois vamos escrever nele (fd[1])
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]);
// 		close(fds[0]);
// 		//executa arvore (t_ast->left);
//		//clear_child_process(exec);
// 		exit(exec->exit_status);
// 	}
// 	//a partir daqui será o processo pai
// 	//Como pipe foi chamado dentro do fork nao precisamos restaurar os canais de leitura e escrita do pai
// 	//MAS precisamos fechar os fds do pipe pois nao iremos usar mais
// 	close(fds[0]);
// 	close(fds[1]);
// 	//Tbm precisamos adicionar a espera e captura dos status dos processos filhos. 
// 	// Esperamos o da esquerda para ele não virar zumbi (o processo termina mas o sistema n recebe o aviso)
// 	waitpid(pid_left, NULL, 0); 

// 	// Esperamos o da direita e guardamos o status dele para alimentar a variavel $?
// 	waitpid(pid_right, &status, 0);

// 	// Antes de alimentar a variavel precisamos tratar o status recebido, transformando ele noTratamos o status da direita para pegar o valor real (0-255)
// 	if (WIFEXITED(status)) //Wait IF EXITED -> retorna verdadeiro se o processo terminou com return ou exit
// 		exec->exit_status = WEXITSTATUS(status); //Pega o estatus de saida real, o n de 0 a 255 é convertido pro 0, 1 , 127 da funçao filho
// 	else if (WIFSIGNALED(status)) //Wait IF SIGNALED -> returna vdd se o filho encerrou por algum sinal
//     	exec->exit_status = 128 + WTERMSIG(status); // extrai o numero do sinal e soma com 128 (padrao do linux)
// 	printf("exit code (pipe.c) = %d\n", exec->exit_status);
// }

