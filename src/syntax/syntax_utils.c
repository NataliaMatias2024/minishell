#include "minishell.h"

void err_msg(char *lex)
{
	char	*msg;

	msg = "minishell: syntax error near unexpected token `";
	if (!lex)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putendl_fd(lex, 2);
	ft_putstr_fd("' \n", STDERR_FILENO);
}