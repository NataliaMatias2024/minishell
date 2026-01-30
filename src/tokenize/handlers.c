#include "minishell.h"

t_token *handler_pipe(const char *input, int *i)
{
	t_token	*token;

	token = new_token(TK_PIPE, ft_strdup("|")); //TODO new_token
	if (!token)
		return (NULL);
	*i += 1;
	return (token);
}
