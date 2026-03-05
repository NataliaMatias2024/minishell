/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkitano <mkitano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:18:28 by mkitano           #+#    #+#             */
/*   Updated: 2026/02/28 11:18:30 by mkitano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_node_type
{
	ND_CMD,
	ND_PIPE,
}	t_node_type;

typedef struct s_redir
{
	t_tk_kind		kind;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
// usado só se for ND_CMD
	char			**arg;
	t_redir			*redir_lst;
}	t_ast;

t_ast	*build_ast(t_node *start, t_node *end);
t_ast	*create_pipe_nd(t_node *pipe, t_node *start, t_node *end);
t_ast	*create_cmd_nd(t_node *start, t_node *end);

char	**fill_arg(t_node *start, t_node *end);
t_redir	*extr_redir(t_node *start, t_node *end);

void	free_ast(t_ast *node);
void	free_pipe(t_ast *node);
void	free_cmd(t_ast *node);
void 	free_argv(char **argv);
void	free_redir(t_redir *head);

#endif