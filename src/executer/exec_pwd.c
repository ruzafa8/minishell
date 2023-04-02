#include "minishell.h"

int exec_pwd()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s", pwd);
	return (0);
}
