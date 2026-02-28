#include "minishell.h"

t_redir *fill_redir_lst()

t_ast *create_pipe_nd(t_node *pipe, t_node *start, t_node *end)

t_ast *create_cmd_nd(t_node *start, t_node *end)

t_node *find_pipe(t_node *start, t_node *end)
{
	t_node *curr;

	curr = start;
	while (curr)
	{
		if (((t_token *)curr->data)->kind == TK_PIPE)
			return (curr);
		if (curr == end)
			break;
		curr = curr->next;
	}
	return (NULL);
}

//depois usa na main de forma recursiva
t_ast *build_ast(t_node *start, t_node *end)
{
	t_node	*pipe_nd;

	if(!start)
		return(NULL);
	pipe_nd = find_pipe(start, end)
	if(pipe_nd)
		return(create_pipe_nd(pipe_nd, start, end));
	return(create_cmd_nd(start, end))
}
 