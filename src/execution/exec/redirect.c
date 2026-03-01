/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:41:48 by namatias          #+#    #+#             */
/*   Updated: 2026/02/28 23:39:54 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_all_redirections(t_exec *exec,  t_dlist *mock_redirs)
{
	t_redir	*content;
	t_node	*current;
	int		status;

	status = 1;
	current = mock_redirs->head; //faz o t_node apontar para o primeiro node
	while (current) //percorre toda a lista de redirecs da linha digitada
	{
		content = (t_redir *)current->data;
		//chama a função correspondende e salva o retorno na variavel status
		if (content->kind == REDIR_IN) // <
			// printf ("Tipo < : 1\n");
			status = handle_redir_in(content->filename);
		else if (content->kind == REDIR_OUT) // >
			//printf ("Tipo > : 2\n");
			status = handle_redir_output(content->filename);
		else if (content->kind == HEREDOC) // <<
			// printf ("Tipo << : 3\n");
			status = handle_heredoc(content->filename, exec);
		else if (content->kind == APPEND) // >>
			status = handle_append(content->filename);
		// Se QUALQUER redirecionamento falhar, paramos por aqui
        if (status != 0)
            break ;
		current = current->next;
	}
	exec->exit_status = status; //atualiza a variavel do exec ($?), com o retorno OU 1
}

int	handle_redir_in(char *filename)
{
	//< direciona o conteudo de um arquivo para a tela!, funcio como uma especie de cat arquivo.txt
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1) //na falha open retorna -1
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_redir_output(char *filename)
{
// > direciona  o output, ao inves de sair no terminal sai no arquivo especificado.
//SE o arquivo n existir ele é criado SE existir seu conteudo é sobrescrito E truncado para tamanho 0
	int	fd;

//O_CREAT -> SE nome n existir cria um arq. padrao
//O_TRUNC -> caso o arq exista trunca para tamnho 0
//0644 -> permissao de ler e escrever para o cargo owner
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) //na falha open retorna -1
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (1);
	}
	//dup2 faz uma cópia do fd antigo para o fd novo, ou seja,
	// o fd gerado pelo open passa a substituir o fd STDOUT padrao.
	//assim ao inves da saida ser o terminal d saida padrao passa a ser o do arquivo aberto.
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_append(char *filename)
{
//>>, direciona o output porem nao sobrecresve se ja tiver info no arquivo.
//SE o arquivo n existir ele é criado SE existir o novo testo é colocado ao final do já existente
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1) //na falha open retorna -1
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (1);
	}
	if(dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
