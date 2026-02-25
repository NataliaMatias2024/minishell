#include "minishell"

int	is_operartor(t_token *token)
{
	t_tk_kind	kind;

	kind = token->kind;
	if (kind == TK_PIPE)
		return (TK_PIPE);
	else if (kind == TK_EOF)
		return (TK_EOF);
	return (-1);
}

int	is_redir(t_token *token)
{
	t_tk_kind	kind;

	kind = token->kind;
		if (kind == TK_IN)
		return (TK_IN);
	else if (kind == TK_OUT)
		return (TK_OUT);
	else if (kind == TK_APPEND)
		return (TK_APPEND);
	else if (kind == TK_HEREDOC)
		return (TK_HEREDOC);
	return (-1);
}
