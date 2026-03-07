/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:13:52 by namatias          #+#    #+#             */
/*   Updated: 2026/03/07 15:36:45 by namatias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "environment.h"
# include "token.h"
# include "builtin.h"
# include "expansion.h"
# include "signals.h"

typedef struct s_ast	t_ast;
typedef struct s_redir	t_redir;

typedef struct s_executor
{
	t_env	*env_list;
	t_ast	*ast_root;
	int		exit_status;
	int		backup_stdin;
	int		backup_stdout;
}			t_exec;

void	exec_ast(t_exec *exec, t_ast *root, int in_pipe);
void	exec_pipe(t_exec *exec, t_ast *node);
int		execute_commands_handler(t_exec *exec, t_ast *node, int in_pipe);
void	exec_external_command(t_exec *exec, char **cmd_args);

char	**transform_env_list(t_env *env_list);
char	*create_path_array(t_env *env_list, char **cmd_args);

int		ft_is_space(char *line);
void	free_split(char **splited);
char	**tokens_to_argv(t_dlist *tklst);
char	*get_env_path(t_env **env, char *name);

int		handle_append(char *filename);
int		handle_redir_in(char *filename);
int		handle_redir_output(char *filename);
int		apply_all_redirections(t_exec *exec, t_redir *redir_list);

int		check_delimiter(char *delimiter);
char	*expand_heredoc(t_exec *exec, char *line);
int		scan_ast_heredocs(t_exec *exec, t_ast *node);
int		handle_heredoc(char *delimiter, t_exec *exec);
int		check_and_run_heredoc(t_exec *exec, t_redir *redir);
int		create_temp_and_exec(int expand, t_exec *exec, char *clean_quotes);

#endif
