#include "minishell.h"

init_shell_data()
{
	
}


int	main(int argc, char **args, char **env)
{
	(void)argc;
	(void)args;
	char **path;
	t_shell_data	shell_data;

	init_shell_data(shell_data);
	path = get_path(env);
	loop_shell(path, env);
	return (0);
}