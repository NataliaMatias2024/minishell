/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 23:39:06 by namatias          #+#    #+#             */
/*   Updated: 2026/03/04 22:08:54 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_temp(int fd, int expand, t_exec *exec, char *clean_quotes);
static char	*expand_heredoc(t_exec *exec, char *line);
static int	check_delimiter(char *delimiter);

int	handle_heredoc(char *delimiter, t_exec *exec)
{
// <<, Here Documents -> heredoc, ele abre uma nova linha, acumula todas as informaçoes ou linhas digitadas
//lendo de forma dinamica as inf digitadas ao inves d um arquivo pré existente. até encontrar o delimitador!
	int		fd;
	int		expand;
	char	*clean_quotes;

//Quando delimitador esta entre aspas NAO ocorre expansão de variaveis, por isso precisamos analisar 1º
	expand = check_delimiter(delimiter);
//Após analisar limpamos as aspas para poder manipular e criar os arquivos sem ruidos
	clean_quotes = remove_quotes(delimiter);
//Inicalmente criamos um arquivo temporarios, nele que escreveremos de forma dinamica td q o usuario passar
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		return (1);
	}
//Para manter dentro das 25 modularizei o looping que coleta as infos digitadas e passa para o arquivo tmp
	create_temp(fd, expand, exec, clean_quotes);
//em comandos como cat << EOF < arquivo.txt, o cat deve ler o arquivo n o EOF, pois o arquivo q veio por ultimo.
//por isso deixamos o resto do codigo para ser executado pelo applay_all_redirections:
	//Após criar o arquivo tmp redirecionamos a info dele para um comando mostrar na tela (igual o redir_in)
	// 	handle_redir_in(".heredoc_tmp");
	//essa funçao deleta nosso arquivo temp, fazendo o heredoc "imprimir na tela" sem criar arquivos na pasta
	// 	unlink(".heredoc_tmp");
	return (0);
}

static void	create_temp(int fd, int expand, t_exec *exec, char *clean_quotes)
{
//Essa funçao recebe o fd do arquivo temp para escrever a info nele
//o int expand para saber se precisa expandir os $ ou n
//exec para caso precise conseguir expandir as variaveis
//delimitar sem quotes para poder verificar e finalizar o looping de escrita
	char	*line;

	while (1)
	{
//Cria a nova lina com o > para o usuario digitar oq quiser
		line = readline("> ");
		if(!line) //usuario usou algum atalho para encerrar o looping
		{
			// if (variavel_global == SIGINT) //TODO: SIGINT acusa o uso de ctrl + C
			// {
				close(fd);
				exec->exit_status = 130;
			// }
			break; // Foi apenas o ctrl + D //TODO: status
		}
//Verifica se o delimitar foi digitado e se foi encerra o looping e dar free na ultima linha
		if (ft_strcmp(line, clean_quotes) == 0)
		{
			free(line);
			break ;
		}
//Após receber a linha e ela nao ter o delimitador verificamos se precisamos expandir ou n
//Caso seja preciso expandir, sobrescrevemos as info no line e chamamos a função d expand.
		if (expand == 1)
			line = expand_heredoc(exec, line);
//Responsável por escrever no arquivo de fd indicado E adicionar uma quebra de linha para a nova linha		
		ft_putendl_fd(line, fd);
		free(line);
	}
	close (fd);
}

static int	check_delimiter(char *delimiter)
{
	int	expand;
	//Se houver QUALQUER aspa, o Bash desativa a expansão
    if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
		expand = 0;
    else
		expand = 1;
	return (expand);
}

static char	*expand_heredoc(t_exec *exec, char *line)
{
	int		i;
	char	auxiliar[2];
	char	*analyzed;

	i = 0;
	auxiliar[1] = '\0';
	analyzed = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
			analyzed = handle_dollar(exec, line, &i, analyzed);
		else
		{
			auxiliar[0] = line[i];
			analyzed = join_and_free(analyzed, auxiliar);
			i++;
		}
	}
	return (analyzed);
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
