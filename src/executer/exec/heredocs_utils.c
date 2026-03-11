/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 23:20:38 by namatias          #+#    #+#             */
/*   Updated: 2026/03/11 15:03:08 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_readline_looping(int fd, int exp, t_exec *exec, char *clean_q);

int	create_temp_and_exec(int expand, t_exec *exec, char *clean_quotes)
{
	int		fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		exit (1);
	}
	set_readline_looping(fd, expand, exec, clean_quotes);
	close (fd);
	return (0);
}

static void	set_readline_looping(int fd, int exp, t_exec *exec, char *clean_q)
{
	char	*aux;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, clean_q) == 0)
		{
			free(line);
			break ;
		}
		if (exp == 1)
		{
			aux = expand_heredoc(exec, line);
			free (line);
			line = aux;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	check_delimiter(char *delimiter)
{
	int	expand;

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
