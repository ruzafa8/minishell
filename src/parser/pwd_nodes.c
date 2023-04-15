#include "minishell.h"

t_command_old	*create_pwd()
{
	t_command_old	*res;

	res = (t_command_old *) ft_calloc(1, sizeof(t_command_old));
	if (!res)
		return (0);
	res->data = 0;
	res->type = PWD;
	return (res);
}