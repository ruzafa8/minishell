#include "minishell.h"

int exec_pwd()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	return (0);
}