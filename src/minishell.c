#include "../includes/minishell.h"

int	main(int argc, char **args, char **env)
{
	(void)argc;
	(void)args;
	char **path;
	
	path = get_path(env);
	loop_shell(path, env);
	return (0);
}