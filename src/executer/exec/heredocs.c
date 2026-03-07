/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 23:39:06 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 02:36:09 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// <<, Here Documents -> heredoc, ele abre uma nova linha, acumula todas as informaçoes ou linhas digitadas
//lendo de forma dinamica as inf digitadas ao inves d um arquivo pré existente. até encontrar o delimitador!
//Precisa ser executado primeiro e dentro de um processo filho, pois caso seja cancelado (ctrl + C)
//deve encerrar td a cadeida de execuçao MAS nao deve sair do processo pai	
int	handle_heredoc(char *delimiter, t_exec *exec)
{
	pid_t	pid;
	int		status;
	int		expand;
	char	*clean_quotes;

	set_signals_ignore();
//Quando delimitador esta entre aspas NAO ocorre expansão de variaveis, por isso precisamos analisar 1º
	expand = check_delimiter(delimiter);
//Após analisar limpamos as aspas para poder manipular e criar os arquivos sem ruidos
	clean_quotes = remove_quotes(delimiter);

	pid = fork();
	if (pid == 0) //dentro processo filho
	{
		//Inicalmente criamos um arquivo temporarios, nele que escreveremos de forma dinamica td q o usuario passar
		//Depois de finalizado essas informaçoes sao passadas para o comando/ tela e o arquivo tmp é deletado
		set_signals_default();
		create_temp_and_exec(expand, exec, clean_quotes);
		free (clean_quotes);
		exit (0);
	}
//ja para lidar com os sinais, como usamos o fork precisamos usar o waitpid e tratar os retornos
	waitpid(pid, &status, 0);
	set_signals_interactive();
	if (WIFSIGNALED(status)) //verifica se encerrou devido algum sinal
	{
		exec->exit_status = 128 + WTERMSIG(status);  //seta o status para o codigo q interrompeu o processo
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		free(clean_quotes);
		return (1);
	}
	else if (WIFEXITED(status)) //verifica se saiu normalmente
		exec->exit_status = WEXITSTATUS(status);
	free(clean_quotes);
	return (0);
}

//Essa funçao garante que todos os heredocs serao encontrados e executados PRIMEIRO
int	check_and_run_heredoc(t_exec *exec, t_redir *redir)
{
	while(redir)
	{
		if (redir->kind == TK_HEREDOC)
		{
			if (handle_heredoc(redir->file, exec))
			{
				//quando é encerrado com o ctrl + c
				if (exec->exit_status == 130)
					//como foi encerrado antes da hora, deixou o arquivo temp para trás
					unlink(".heredoc_tmp");
				else
					exec->exit_status = 1;  //acusa o erro, pois só entra dentro do if quando da erro
				return (1); //encerra a execuçao dos comandos, pois heredoc ou deu erro ou foi cancelado
			}
		}
		redir = redir->next;
	}
	//se chegou aqui ja percorreu td a lista e executou os HEREDOCS existentes sem erros
	return (0);
}

int	scan_ast_heredocs(t_exec *exec, t_ast *node)
{
	int	exit_code;
	
	if (!node || !exec)
		return (0);
	
	exit_code = 0;
	//se node for do tipo pipe verificamos ambos os lados para ver se algum tem HEREDOC
	if (node->type == ND_PIPE)
	{
		//O objetivo é achar nodes do timo CMD pois é neles que estará os HEREDOC q precisamos executar primeiro
		if (scan_ast_heredocs(exec, node->left) == 1)
			return (1); //como é uma recursao, retornará 1 quando algum nó CMD da esquerda retornar erro
		if (scan_ast_heredocs(exec, node->right) == 1)
			return (1); //como é uma recursao, retornará 1 quando algum nó CMD da direita retornar erro
	}
	else if (node->type == ND_CMD) //achando o node de comandos verificamos se tem HEREDOC e EXECUTAMOS
	{
		if (node->redir_lst)
			exit_code = check_and_run_heredoc(exec, node->redir_lst);
	}
	return (exit_code);
}
