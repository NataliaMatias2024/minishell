/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 23:20:38 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 02:22:49 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Essa funçao recebe:
//o int expand para saber se precisa expandir os $ ou n
//exec para caso precise conseguir expandir as variaveis
//delimiter sem quotes para poder verificar e finalizar o looping de escrita
//Além disso em comandos como cat << EOF < arquivo.txt, o cat deve ler o arquivo n o EOF
//por isso deixamos o resto do codigo para ser executado pelo applay_all_redirections.
//é nele que ocorre o redirecionamento pro cat ou outros comandos e delet do arquivo temp
int	create_temp_and_exec(int expand, t_exec *exec, char *clean_quotes)
{
	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		exit (1);
	}
	while (1)
	{
		//Cria a nova lina com o > para o usuario digitar oq quiser
		line = readline("> ");
		if(!line) //usuario usou algum atalho para encerrar o looping
			break ;
		//Verifica se o delimitar foi digitado e se foi encerra o looping e da free na ultima linha
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
	return (0);
}

int	check_delimiter(char *delimiter)
{
	int	expand;
	//Se houver QUALQUER aspa, o Bash desativa a expansão
    if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '\"'))
		expand = 0;
    else
		expand = 1;
	return (expand);
}

char	*expand_heredoc(t_exec *exec, char *line)
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

