#ifndef AST_H
# define AST_H

typedef enum e_node_type
{
	ND_CMD
	ND_PIPE
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
// usado só se for ND_CMD
	char			**arg;
	t_redir			*redir_lst;
}	t_redir;

typedef struct s_redir
{
	t_tk_kind	kind;
	char		*file;
	t_redir		*next;
}	t_redir;

#endif