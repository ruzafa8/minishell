#include "minishell.h"

t_command	*create_pwd()
{
	t_command	*res;

	res = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!res)
		return (0);
	res->data = 0;
	res->type = PWD;
	return (res);
}